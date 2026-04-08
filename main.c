#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void run_test(char *filename)
{
    int     fd;
    char    *line;
    int     count = 1;

    printf("\n--- Testing: %s ---\n", filename ? filename : "STDIN");
    
    if (filename)
        fd = open(filename, O_RDONLY);
    else
        fd = 0;

    if (fd < 0)
    {
        printf("Error opening file\n");
        return;
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("[%02d]|%s", count++, line);
        if (line[ft_strlen(line) - 1] != '\n')
            printf("\033[31m[NO_NL]\033[0m");
        free(line);
    }
    
    if (filename)
        close(fd);
    printf("\n--- End of File ---\n");
}

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
            run_test(argv[i]);
        return (0);
    }

    /* Automated Edge Cases */
    
    // 1. Basic File
    system("echo 'line 1\nline 2\nline 3' > test_normal.txt");
    run_test("test_normal.txt");

    // 2. No Newline at End
    system("echo -n 'this has no newline at the end' > test_no_nl.txt");
    run_test("test_no_nl.txt");

    // 3. Empty File
    system("touch test_empty.txt");
    run_test("test_empty.txt");

    // 4. Multiple Newlines
    system("echo '\n\n\n' > test_only_nl.txt");
    run_test("test_only_nl.txt");

    // 5. Invalid FD
    printf("\n--- Testing: Invalid FD ---\n");
    char *err = get_next_line(999);
    if (!err) printf("Invalid FD handled correctly (NULL)\n");
    else free(err);

    // 6. Large File / Big Lines
    system("python3 -c \"print('A' * 5000 + '\\n' + 'B' * 5000)\" > test_big.txt");
    run_test("test_big.txt");

    // 7. Cleanup
    system("rm test_normal.txt test_no_nl.txt test_empty.txt test_only_nl.txt test_big.txt");

    return (0);
}

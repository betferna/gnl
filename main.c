#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Colores para la terminal
#define GREEN "\033[0;32m"
#define RED   "\033[0;31m"
#define RESET "\033[0m"

int check_line(char *got, char *expected)
{
	if (!got && !expected)
		return (1);
	if (!got || !expected)
		return (0);
	return (strcmp(got, expected) == 0);
}

void run_test(char *name, char *file, char **expected, int count)
{
	int fd = open(file, O_RDONLY);
	char *line;
	int i = 0;
	int ok = 1;

	if (fd < 0)
	{
		printf("%s: " RED "Error opening file" RESET "\n", name);
		return;
	}

	while (i < count)
	{
		line = get_next_line(fd);
		if (!check_line(line, expected[i]))
		{
			ok = 0;
			// Opcional: printf("Expected: %s | Got: %s\n", expected[i], line);
		}
		free(line);
		i++;
	}
	// Verificar que después de las líneas esperadas devuelva NULL
	line = get_next_line(fd);
	if (line != NULL)
	{
		ok = 0;
		free(line);
	}

	printf("%-20s: %s\n", name, ok ? GREEN "OK" RESET : RED "KO" RESET);
	close(fd);
}

void test_invalid_fd(void)
{
	char *line = get_next_line(-1);
	printf("%-20s: %s\n", "Invalid FD", (line == NULL) ? GREEN "OK" RESET : RED "KO" RESET);
	if (line) free(line);
}

void create_files(void)
{
	int fd;

	system("touch empty.txt");
	
	fd = open("single_char.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(fd, "a", 1); close(fd);

	fd = open("no_newline.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(fd, "hola", 4); close(fd);

	fd = open("only_newlines.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(fd, "\n\n\n", 3); close(fd);

	fd = open("multiple_lines.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(fd, "line1\nline2\nline3\n", 18); close(fd);
}

int main(void)
{
	create_files();

	printf("--- INICIANDO TESTER GNL ---\n");
	
	test_invalid_fd();

	char *empty[] = {NULL};
	run_test("Empty File", "empty.txt", empty, 0);

	char *single[] = {"a"};
	run_test("Single Char", "single_char.txt", single, 1);

	char *no_nl[] = {"hola"};
	run_test("No Newline End", "no_newline.txt", no_nl, 1);

	char *only_nl[] = {"\n", "\n", "\n"};
	run_test("Only Newlines", "only_newlines.txt", only_nl, 3);

	char *multi[] = {"line1\n", "line2\n", "line3\n"};
	run_test("Multiple Lines", "multiple_lines.txt", multi, 3);

	printf("----------------------------\n");

	// Limpieza de archivos temporales
	system("rm empty.txt single_char.txt no_newline.txt only_newlines.txt multiple_lines.txt");

	return 0;
}

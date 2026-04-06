/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:01:45 by betferna          #+#    #+#             */
/*   Updated: 2026/04/06 11:57:28 by user             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *read_file(int fd, char *storage)
{
    char    *buffer;
    char    *temp;
    int     bytes;

    buffer = calloc((BUFFER_SIZE + 1), sizeof(char));
    if (!buffer)
        return (NULL);
    bytes = 1;
    while (bytes != 0)
    {
        bytes = read(fd, buffer, BUFFER_SIZE);
        if (bytes == -1)
        {
            free(buffer);
            free(storage);
            return (NULL);
        }
        buffer[bytes] = '\0';
        if (!storage)
            storage = ft_strdup("");
        temp = ft_strjoin(storage, buffer);
        free(storage);
        storage = temp;
        if (ft_strchr(buffer, '\n'))
            break;
    }
    free(buffer);
    return (storage);
}

char *get_next_line(int fd)
{
    static char *storage;
    char        *line;
    char        *temp;
    int         i;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    storage = read_file(fd, storage);
    if (!storage || *storage == '\0')
    {
        free(storage);
        storage = NULL;
        return (NULL);
    }
    i = 0;
    while (storage[i] && storage[i] != '\n')
        i++;
    line = ft_substr(storage, 0, i + (storage[i] == '\n'));
    temp = ft_strdup(storage + i + (storage[i] == '\n'));
    free(storage);
    storage = temp;
    return (line);
}

int main(void)
{
    int     fd;
    char    *line;

    fd = open("archivo.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line); 
	free(line);
    }
    close(fd);
    return (0);
}
// void free_storage(char *storage)
// {
//     ft_bzero(storage, ft_strlen(storage));
//     free(storage);
// }

// char *get_line(int fd, char *buffer, char *storage, int size)
// {
//     int 	bytes;
//     bytes = 1;
// 	buffer = calloc((BUFFER_SIZE + 1), (sizeof(char)));
//     while ( bytes != 0)
//     {
//         bytes = read(fd, buffer, BUFFER_SIZE);
//         if (bytes == -1) 
// 	    {
//             free(buffer);
//             free(storage);
//             return NULL;
//         }
//         buffer[bytes] = '\0';
//         temp = ft_strjoin(storage, buffer);
//         free(storage);
//         storage = temp;
//     }
//     free(buffer);
//     if (!storage) retorn NULL;
//     if (!(ft_strchr(storage, '\n')))
//     {
//         get_line(buffer, storage, BUFFER_SIZE*2);
//     }
//     return (storage);
// }

// char *get_next_line(int fd)
// {
//     static char *storage;
//     char        *line;
//     char        *buffer;
// 	if (fd < 0 || (BUFFER_SIZE <= 0))
//         return NULL;
//     else if
//         line = get_line(fd, storage, buffer, BUFFER_SIZE);
//     free_storage(storage);  
//     return (line);
// }

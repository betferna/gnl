/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: betferna <betferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:45:04 by betferna          #+#    #+#             */
/*   Updated: 2026/04/13 15:44:40 by betferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_storage(char *storage)
{
	if (storage)
	{
		free(storage);
		storage = NULL;
	}
	return (NULL);
}

char	*find_newline(char *st)
{
	char	*line;
	int		i;
	int		len;

	len = ft_strlen(st) + 2;
	if (!st)
		return (NULL);
	line = malloc(sizeof(char) * len);
	if (!line)
		return (NULL);
	i = 0;
	while (st[i] && st[i] != '\n')
	{
		line[i] = st[i];
		i++;
	}
	if (st[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*left_line(char *storage)
{
	int		i;
	char	*temp;

	i = 0;
	while (storage[i] && storage[i] != '\n')
		i++;
	if (!storage[i] || !storage[i + 1])
	{
		free(storage);
		return (NULL);
	}
	temp = ft_substr(storage, i + 1, ft_strlen(storage));
	free(storage);
	return (temp);
}

char	*ft_read(int fd, char *storage, char *buffer)
{
	int		bytes;
	char	*temp;

	bytes = 0;
	while (!newline(storage))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == 0)
			break ;
		else if (bytes == -1 || !storage)
		{
			storage = free_storage(storage);
			free(buffer);
			return (NULL);
		}
		buffer[bytes] = '\0';
		temp = storage;
		storage = ft_strjoin(temp, buffer);
		free(temp);
	}
	free(buffer);
	if (!storage || *storage == '\0')
		storage = free_storage(storage);
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((sizeof(char) * BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (!storage)
		storage = ft_strdup("");
	storage = ft_read(fd, storage, buffer);
	if (!storage)
		return (NULL);
	line = find_newline(storage);
	storage = left_line(storage);
	return (line);
}

// int main()
// {
// 	char *line;
// 	int fd = open("file.txt", O_RDWR | O_CREAT);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	line = NULL;
// 	close(fd);
// 	// remove("file.txt");
// 	return(0);
// }

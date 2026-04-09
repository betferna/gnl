/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: betferna <betferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:45:04 by betferna          #+#    #+#             */
/*   Updated: 2026/04/09 15:12:31 by betferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*free_storage(char *storage)
{
	if (storage)
	{
		free(storage);
		storage = NULL;
	}
	return (NULL);
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
			storage = free_storage(storage);
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

char	*get_next_line(int fd)
{
	static char	*storage[1024];
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((sizeof(char) * BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (!storage[fd])
		storage[fd] = ft_strdup("");
	storage[fd] = ft_read(fd, storage[fd], buffer);
	if (!storage[fd])
		return (NULL);
	line = find_newline(storage[fd]);
	storage[fd] = left_line(storage[fd]);
	return (line);
}

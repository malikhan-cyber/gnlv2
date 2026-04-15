/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkhan <alkhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:47:07 by alkhan            #+#    #+#             */
/*   Updated: 2026/04/15 15:11:25 by alkhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			read_check;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
	{
		buffer = ft_strdup("");
		if (!buffer)
			return (NULL);
	}
	read_check = read_until_newline(&buffer, fd);
	if (read_check == -1)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = get_newline(&buffer);
	return (line);
}

int	read_until_newline(char **buffer, int fd)
{
	char	*tempbuffer;
	int		bytes_read;

	bytes_read = 1;
	tempbuffer = malloc(BUFFER_SIZE + 1);
	if (!tempbuffer)
		return (free(tempbuffer), -1);
	while (!ft_strchr(*buffer, SEARCH_CHAR) && bytes_read > 0)
	{
		bytes_read = read(fd, tempbuffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		tempbuffer[bytes_read] = '\0';
		if (join_buffer(buffer, tempbuffer) == -1)
			return (free(tempbuffer), -1);
	}
	free(tempbuffer);
	if (bytes_read == 0)
		return (0);
	if (bytes_read < 0)
		return (-1);
	return (1);
}

char	*get_newline(char **buffer)
{
	char	*line;
	int		len;
	char	*ptr;

	if (!*buffer)
		return (NULL);
	if (!*buffer || **buffer == '\0')
	{
		free(*buffer);
		*buffer = (NULL);
		return (NULL);
	}
	ptr = ft_strchr(*buffer, SEARCH_CHAR);
	if (ptr == NULL)
		return (line = ft_strdup(*buffer), free(*buffer), *buffer = NULL, line);
	len = ptr - *buffer + 1;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, *buffer, len);
	line[len] = '\0';
	if (update_buffer(buffer, ptr) == -1)
    {
        free(line); // Voorkom lek als we in een error-state eindigen
        return (NULL);
    }
	return (line);
}

int	join_buffer(char **buffer, char *tempbuffer)
{
	char	*oud;
	char	*joined;

	oud = *buffer;
	joined = ft_strjoin(oud, tempbuffer);
	if (!joined)
		return (free(*buffer),  *buffer = NULL, -1);
	free(oud);
	*buffer = joined;
	return (1);
}

int	update_buffer(char **buffer, char *ptr)
{
	char	*rest;

	if (*(ptr + 1) == '\0')
    {
        free(*buffer);
        *buffer = NULL;
        return (1);
    }
	rest = ft_strdup(ptr + 1);
	if (!rest)
		return (free(*buffer),*buffer = NULL, -1);
	free(*buffer);
	*buffer = rest;
	return (1);
}

// int	main(void)
// {
// 	int fd;
// 	char *line;

// 	fd = open("test.txt", O_RDONLY);
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		if ((ft_strchr(line, SEARCH_CHAR)) == NULL)
// 			break ;
// 		free(line);
// 	}
// 	free(line);
// 	close(fd);
// 	return (0);
// }
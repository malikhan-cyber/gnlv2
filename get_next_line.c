/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:47:07 by alkhan            #+#    #+#             */
/*   Updated: 2026/04/11 22:33:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
		buffer = ft_strdup("");
	if (read_until_newline(&buffer, fd) == -1)
   		return (NULL);	
	line = get_newline(&buffer);
	return (line);
}
int read_until_newline(char **buffer, int fd)
{
    char    *tempbuffer;
    int     bytes_read;

    tempbuffer = malloc(BUFFER_SIZE + 1);
    if (!tempbuffer)
        return (-1);
    while (!ft_strchr(*buffer, SEARCH_CHAR))
    {
        bytes_read = read(fd, tempbuffer, BUFFER_SIZE);
        if (bytes_read < 0)
            break;
        if (bytes_read == 0)
            break;
        tempbuffer[bytes_read] = '\0';
        if (join_buffer(buffer, tempbuffer) == -1)
            break;
    }
    free(tempbuffer);
    if (bytes_read < 0)
        return (-1);
    return (1);
}

int join_buffer(char **buffer, char *tempbuffer)
{
	char *oud;
	
	oud = *buffer;
	*buffer = ft_strjoin(*buffer, tempbuffer);
	free(oud);
		if (!*buffer)
			return (-1);
	return (1);
}
char	*free_gnl(char **buffer, char **tempbuffer)
{
	free(*buffer);
	free(*tempbuffer);
	*buffer = NULL;
	*tempbuffer = NULL;
	return (NULL);
}

char	*get_newline(char **buffer)
{
	char	*line;
	int		len;
	char	*ptr;

	ptr = ft_strchr(*buffer, SEARCH_CHAR);
	if (ptr == NULL)
	{
		line = ft_strdup(*buffer);
		return (line);
	}
	len = (ptr - *buffer) + 1;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, *buffer, len);
	line[len] = '\0';
	update_buffer(buffer, ptr);
	return (line);
}

void	update_buffer(char **buffer, char *ptr)
{
	char	*rest;

	rest = ft_strdup(ptr + 1);
	if(!rest)
		return ;
	free(*buffer);
	*buffer = rest;
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("testbestand.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		printf("%s", line);
		if ((ft_strchr(line, SEARCH_CHAR)) == NULL)
			break ;
		free(line);
	}
	close(fd);
	return (0);
}

 
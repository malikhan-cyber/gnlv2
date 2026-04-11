#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		tempbuffer[BUFFER_SIZE + 1];
	int			bytes_read;
	char		*ptr;
	char		*line;
	int			len;
	char		*rest;

	if (!buffer)
		buffer = ft_strdup("");
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while ((ft_strchr(buffer, '\n')) == NULL)
	{
		bytes_read = read(fd, tempbuffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		if (bytes_read == 0)
			break ;
		tempbuffer[bytes_read] = '\0';
		buffer = ft_strjoin(buffer, tempbuffer);
	}
    if	((bytes_read == 0) && (ft_strchr(buffer, SEARCH_CHAR) == NULL) && (buffer[0] == '\0'))
        return (NULL);
	ptr = ft_strchr(buffer, '\n');
	if (ptr == NULL)
	{
		line = ft_strdup(buffer);
		free(buffer);
		buffer = NULL;
		return (line);
	}
	len = (ptr - buffer) + 1;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, buffer, len);
	line[len] = '\0';
	rest = ft_strdup(ptr + 1);
	free(buffer);
	buffer = rest;
	return (line);
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
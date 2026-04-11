/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkhan <alkhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 11:34:23 by alkhan            #+#    #+#             */
/*   Updated: 2026/04/11 13:54:15 by alkhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *str, int c)
{
	int				i;
	unsigned char	cc;

	if (!str)
		return (NULL);
	cc = (unsigned char)c;
	i = 0;
	while (str[i])
	{
		if (str[i] == cc)
			return ((char *)&str[i]);
		i++;
	}
	if (cc == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

char	*ft_strdup(const char *str)
{
	int		i;
	char	*ptr;
	int		len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	ptr = malloc((len + 1) * sizeof(char));
	if (!ptr)
	{
		free(ptr);
		return (NULL);
	}
	i = 0;
	while (str[i])
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		len;
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	len = (ft_strlen(s1) + ft_strlen(s2));
	ptr = malloc(len + 1);
	if (ptr == 0)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[j])
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	return (ptr);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*cdest;
	unsigned char	*csrc;

	csrc = (unsigned char *)src;
	cdest = (unsigned char *)dest;
	if (dest == 0 && src == 0)
		return (dest);
	i = 0;
	while (i < n)
	{
		cdest[i] = csrc[i];
		i++;
	}
	return (dest);
}

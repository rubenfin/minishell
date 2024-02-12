/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 10:50:42 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/12 15:04:21 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/get_next_line.h"

void	*ft_free_gnl(char **line, char **buffer, int arg)
{
	if (arg == 1)
	{
		if (*line)
			free(*line);
		*line = NULL;
	}
	if (arg == 2)
	{
		if (*line)
			free(*line);
		*line = NULL;
		if (*buffer)
			free(*buffer);
		*buffer = NULL;
	}
	return (NULL);
}

int	ft_strlen_gnl(char *str)
{
	size_t	i;

	i = 0;
	if (!str || !str[i])
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strncpy_gnl(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (!dest || !src)
		return (dest);
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*full_s;
	int		i;

	if (!s1)
		return (ft_strdup_gnl(s2));
	if (ft_strlen_gnl(s1) + ft_strlen_gnl(s2) == 0)
		return (ft_free_gnl(&s1, NULL, 1));
	full_s = (char *)malloc(((ft_strlen_gnl(s1) + ft_strlen_gnl(s2)) + 1)
			* sizeof(char));
	if (!full_s)
		return (ft_free_gnl(&s1, NULL, 1));
	i = 0;
	while (s1[i])
	{
		full_s[i] = s1[i];
		i++;
	}
	while (*s2)
		full_s[i++] = *(s2++);
	full_s[i] = '\0';
	ft_free_gnl(&s1, NULL, 1);
	return (full_s);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s || !c)
		return (NULL);
	if (c == '\0')
		return ((char *)&s[ft_strlen_gnl((char *)s)]);
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:33:55 by abidolet          #+#    #+#             */
/*   Updated: 2025/07/06 14:45:35 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft/get_next_line.h"

static ssize_t	process_result(char *delim_ptr, char *line,
	char *buffer, char **restrict lineptr)
{
	ssize_t	size;
	char	*tmp;

	if (!delim_ptr)
	{
		*lineptr = line;
		return (-1);
	}
	size = delim_ptr - line + 1;
	ft_strlcpy(buffer, delim_ptr + 1, BUFFER_SIZE + 1);
	tmp = ft_strndup(line, size);
	free(line);
	if (!tmp)
		return (-1);
	*lineptr = tmp;
	return (size);
}

static char	*find_delim(const int fd, char *buffer, char **line,
	const int delim)
{
	char		*delim_ptr;
	long long	bytes_read;
	char		*tmp;

	delim_ptr = ft_strchr(*line, delim);
	while (!delim_ptr)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(*line);
			*line = NULL;
			return (NULL);
		}
		else if (bytes_read == 0)
			return (delim_ptr);
		buffer[bytes_read] = '\0';
		tmp = *line;
		*line = ft_strjoin(*line, buffer);
		free(tmp);
		if (!*line)
			return (NULL);
		delim_ptr = ft_strchr(*line, delim);
	}
	return (delim_ptr);
}

static _Bool	init_line(char **line, size_t *restrict n, char *buffer)
{
	char	*tmp;

	if (!*line || *n == 0)
	{
		*n = BUFFER_SIZE;
		*line = malloc(*n);
		if (!*line)
			return (1);
		(*line)[0] = '\0';
	}
	if (buffer[0])
	{
		tmp = *line;
		*line = ft_strjoin(*line, buffer);
		free(tmp);
		if (!*line)
			return (1);
	}
	return (0);
}

ssize_t	ft_getdelim(char **restrict lineptr, size_t *restrict n,
	int delim, int fd)
{
	static char	buffer[FD_MAX][BUFFER_SIZE + 1];
	char		*line;
	char		*delim_ptr;

	if (!lineptr || !n || fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0)
		return (-1);
	line = *lineptr;
	if (init_line(&line, n, buffer[fd]))
		return (-1);
	delim_ptr = find_delim(fd, buffer[fd], &line, delim);
	if (!line)
		return (-1);
	return (process_result(delim_ptr, line, buffer[fd], lineptr));
}

inline ssize_t	ft_getline(char **restrict lineptr,
	size_t *restrict n, int fd)
{
	return (ft_getdelim(lineptr, n, '\n', fd));
}

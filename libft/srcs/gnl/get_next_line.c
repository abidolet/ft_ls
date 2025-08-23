/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:16:22 by abidolet          #+#    #+#             */
/*   Updated: 2025/02/16 00:17:56 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/get_next_line.h"

static char	*find_newline(const int fd, char *buffer, char **line,
	char *newline)
{
	ssize_t	bytes_read;
	char	*tmp;

	while (!newline)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(*line);
			*line = NULL;
			return (NULL);
		}
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		tmp = *line;
		*line = ft_strjoin(*line, buffer);
		free(tmp);
		newline = ft_strchr(*line, '\n');
	}
	return (newline);
}

char	*get_next_line(int fd)
{
	static char	buffer[FD_MAX][BUFFER_SIZE + 1];
	char		*line;
	char		*newline;
	char		*tmp;

	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	if (buffer[fd][0])
	{
		line = ft_strdup(buffer[fd]);
		if (!line)
			return (NULL);
	}
	newline = find_newline(fd, buffer[fd], &line, ft_strchr(line, '\n'));
	if (newline)
	{
		ft_strcpy(buffer[fd], newline + 1);
		tmp = line;
		line = ft_strndup(line, newline - line + 1);
		free(tmp);
	}
	else
		buffer[fd][0] = '\0';
	return (line);
}

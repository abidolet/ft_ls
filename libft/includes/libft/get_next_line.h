/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:16:59 by abidolet          #+#    #+#             */
/*   Updated: 2025/07/06 14:45:17 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "libft/str.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define FD_MAX 1024

char	*get_next_line(int fd);
ssize_t	ft_getdelim(char **restrict lineptr, size_t *restrict n, int delim,
			int fd);
ssize_t	ft_getline(char **restrict lineptr, size_t *restrict n, int fd);

#endif

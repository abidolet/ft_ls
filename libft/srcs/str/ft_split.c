/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 23:19:08 by abidolet          #+#    #+#             */
/*   Updated: 2025/02/15 23:19:08 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/str.h"

static size_t	count_words(const char *s, char c)
{
	size_t	res;

	res = 0;
	while (*s)
	{
		res++;
		while (*s && *s != c)
			s++;
		while (*s && *s == c)
			s++;
	}
	return (res);
}

void	*free_arr(void **arr)
{
	size_t	i;

	if (arr)
	{
		i = 0;
		while (arr[i])
			free(arr[i++]);
		free(arr);
		arr = NULL;
	}
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char		**res;
	size_t		i;
	const char	*tmp;

	if (!s)
		return (NULL);
	while (*s && *s == c)
		s++;
	res = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (*s)
	{
		tmp = s;
		while (*s && *s != c)
			s++;
		res[i] = ft_strndup(tmp, s - tmp);
		if (!res[i++])
			return (free_arr((void **)res));
		while (*s && *s == c)
			s++;
	}
	res[i] = NULL;
	return (res);
}

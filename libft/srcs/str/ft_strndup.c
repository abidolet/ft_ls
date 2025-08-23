/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 23:37:34 by abidolet          #+#    #+#             */
/*   Updated: 2025/07/06 15:08:35 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/str.h"
#include <stdlib.h>

char	*ft_strndup(const char *s, size_t n)
{
	char	*res;
	size_t	size;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (n > size)
		n = size;
	res = malloc(n + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s, n + 1);
	return (res);
}

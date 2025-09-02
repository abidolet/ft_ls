/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 22:28:44 by abidolet          #+#    #+#             */
/*   Updated: 2025/02/15 22:28:44 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/str.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (start >= size)
		len = 0;
	if (size - start < len)
		len = size - start;
	return (ft_strndup(s + start, len));
}

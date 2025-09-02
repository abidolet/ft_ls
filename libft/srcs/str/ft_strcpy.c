/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 22:58:53 by abidolet          #+#    #+#             */
/*   Updated: 2025/07/06 15:13:42 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/str.h"

char	*ft_strcpy(char *dest, const char *src)
{
	size_t	size_src;

	size_src = ft_strlen(src) + 1;
	while (size_src--)
		dest[size_src] = src[size_src];
	return (dest);
}

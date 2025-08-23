/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 20:18:55 by abidolet          #+#    #+#             */
/*   Updated: 2025/07/06 15:16:19 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	if (!dest && !src)
		return (dest);
	while (n-- > 0)
		((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
	return (dest);
}

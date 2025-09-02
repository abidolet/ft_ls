/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 00:00:06 by abidolet          #+#    #+#             */
/*   Updated: 2024/11/22 00:00:06 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	void	*res;

	if (!dest && !src)
		return (NULL);
	res = dest;
	if (dest < src || (unsigned char *)dest >= (unsigned char *)src + n)
		while (n--)
			*(unsigned char *)dest++ = *(unsigned char *)src++;
	else
		while (n--)
			*((unsigned char *)dest + n) = *((unsigned char *)src + n);
	return (res);
}

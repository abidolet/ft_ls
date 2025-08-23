/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 23:12:12 by abidolet          #+#    #+#             */
/*   Updated: 2025/02/15 23:12:12 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	while (n-- > 0)
		if (*((unsigned char *)s1++) != *((unsigned char *)s2++))
			return (*((unsigned char *)s1 - 1) - *((unsigned char *)s2 - 1));
	return (0);
}

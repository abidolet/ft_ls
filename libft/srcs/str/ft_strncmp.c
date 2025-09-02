/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:06:23 by abidolet          #+#    #+#             */
/*   Updated: 2025/02/15 21:23:04 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n-- && (*s1 || *s2) && *s1++ == *s2++)
		;
	if (n + 1 == 0)
		return (0);
	return ((unsigned char)*(s1 - 1) - (unsigned char)*(s2 - 1));
}

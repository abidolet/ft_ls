/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:14:41 by abidolet          #+#    #+#             */
/*   Updated: 2025/01/14 17:14:41 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_itoa(int n)
{
	long			nb;
	unsigned long	size;
	char			*res;

	nb = n;
	size = (n <= 0);
	while (n && ++size)
		n /= 10;
	res = malloc(size + 1);
	if (!res)
		return (NULL);
	if (nb < 0)
	{
		res[0] = '-';
		nb = -nb;
	}
	res[size--] = 0;
	while (nb > 9)
	{
		res[size--] = nb % 10 + '0';
		nb /= 10;
	}
	res[size] = nb + '0';
	return (res);
}

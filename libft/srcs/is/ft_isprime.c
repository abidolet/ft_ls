/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprime.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 00:35:27 by abidolet          #+#    #+#             */
/*   Updated: 2025/07/04 23:47:38 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/math.h"

int	ft_isprime(unsigned long n)
{
	const unsigned long	max_divisor = ft_sqrt(n) + 1;
	unsigned long		i;

	if (n % 2 == 0 || n < 2)
		return (n == 2);
	i = 3;
	while (i <= max_divisor)
	{
		if (n % i == 0)
			return (0);
		i += 2;
	}
	return (1);
}

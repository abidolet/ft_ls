/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 00:48:31 by abidolet          #+#    #+#             */
/*   Updated: 2025/07/02 22:19:05 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/is.h"

int	ft_atoi_base(const char *str, int str_base)
{
	int		sign;
	long	res;

	if (!str || str_base < 2 || str_base > 36)
		return (0);
	sign = 1;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1;
	res = 0;
	while (*str)
	{
		res *= str_base;
		if (ft_isdigit(*str))
			res += *str - '0';
		else if (ft_isalpha(*str))
			res += *str - ('A' + (ft_islower(*str)) * 32) + 10;
		if (res * sign != (int)(res * sign))
			return (-1);
		str++;
	}
	return (res * sign);
}

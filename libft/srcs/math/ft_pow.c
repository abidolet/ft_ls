/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 00:18:38 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/11 16:22:28 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/math.h"

double	ft_pow(double base, double exp)
{
	if (base == 0.0)
		return (0.0);
	else if (exp == 0)
		return (1.0);
	else if (exp < 0)
		return (1.0 / ft_pow(base, -exp));
	else if (exp == (int)exp)
	{
		if ((int)exp % 2 == 0)
			return (ft_pow(base * base, exp * 0.5));
		else
			return (base * ft_pow(base * base, (exp - 1) * 0.5));
	}
	return (ft_exp(exp * ft_log(base)));
}

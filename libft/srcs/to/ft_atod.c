/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 23:40:04 by abidolet          #+#    #+#             */
/*   Updated: 2025/07/06 16:37:21 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/is.h"
#include "libft/limits.h"
#include "libft/math.h"

static void	get_exponent(const char *nptr, double *res)
{
	int				exponent;
	const int		max_exponent = 308;
	int				exp_sign;
	const double	nan = 0.0 / 0.0;
	double			power;

	exponent = 0;
	exp_sign = 1;
	if (*nptr == '+' || *nptr == '-')
		if (*nptr++ == '-')
			exp_sign = -1;
	while (ft_isdigit(*nptr))
	{
		exponent = exponent * 10 + (*nptr++ - '0');
		if (exponent > max_exponent)
		{
			*res = nan;
			return ;
		}
	}
	power = ft_pow(10.0, exponent * exp_sign);
	if (power == 0.0)
		*res = nan;
	else
		*res *= power;
}

static void	get_decimal(const char *nptr, double *res)
{
	double			frargction;
	const int		precision = 15;
	int				decimal;

	frargction = 1.0;
	decimal = 0;
	while (ft_isdigit(*nptr) && decimal++ <= precision)
	{
		frargction /= 10.0;
		*res += (*nptr++ - '0') * frargction;
	}
	if (*nptr == 'e' || *nptr == 'E')
		get_exponent(++nptr, res);
}

double	ft_atod(const char *nptr)
{
	double			res;
	int				sign;
	const double	nan = 0.0 / 0.0;

	if (!nptr)
		return (nan);
	res = 0.0;
	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		if (*nptr++ == '-')
			sign = -1;
	while (ft_isdigit(*nptr))
	{
		if (res > (DBL_MAX - (*nptr - '0')) / 10.0)
			return (nan);
		res = res * 10 + *nptr++ - '0';
	}
	if (*nptr == '.')
		get_decimal(++nptr, &res);
	return (res * sign);
}

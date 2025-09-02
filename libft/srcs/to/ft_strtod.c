/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 23:39:27 by abidolet          #+#    #+#             */
/*   Updated: 2025/07/06 16:37:21 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/is.h"
#include "libft/limits.h"
#include "libft/math.h"

static void	get_exponent(char **endptr, double *res)
{
	int				exponent;
	const int		max_exponent = 308;
	int				exp_sign;
	const double	nan = 0.0 / 0.0;
	double			power;

	exponent = 0;
	exp_sign = 1;
	if (**endptr == '+' || **endptr == '-')
		if (*(*endptr)++ == '-')
			exp_sign = -1;
	while (ft_isdigit(**endptr))
	{
		exponent = exponent * 10 + (*(*endptr)++ - '0');
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

static void	get_decimal(char **endptr, double *res)
{
	double			frargction;
	const int		precision = 15;
	int				decimal;

	(*endptr)++;
	frargction = 1.0;
	decimal = 0;
	while (ft_isdigit(**endptr) && decimal++ <= precision)
	{
		frargction /= 10.0;
		*res += (*(*endptr)++ - '0') * frargction;
	}
	if (**endptr == 'e' || **endptr == 'E')
	{
		(*endptr)++;
		get_exponent(endptr, res);
	}
}

double	ft_strtod(const char *nptr, char **endptr)
{
	double			res;
	int				sign;
	const double	nan = 0.0 / 0.0;

	if (!nptr)
		return (nan);
	endptr = (char **)&nptr;
	res = 0.0;
	sign = 1;
	while (ft_isspace(**endptr))
		(*endptr)++;
	if (**endptr == '+' || **endptr == '-')
		if (*(*endptr)++ == '-')
			sign = -1;
	while (ft_isdigit(**endptr))
	{
		if (res > (DBL_MAX - (**endptr - '0')) / 10.0)
			return (nan);
		res = res * 10 + *(*endptr)++ - '0';
	}
	if (**endptr == '.')
		get_decimal(endptr, &res);
	return (res * sign);
}

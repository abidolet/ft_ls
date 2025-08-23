/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trigo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 10:22:40 by abidolet          #+#    #+#             */
/*   Updated: 2025/07/06 16:35:30 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/math.h"
#include "libft/limits.h"

double	ft_mod(double x, double y)
{
	if (y == 0.0)
		return (0.0 / 0.0);
	return (x - (double)(long long)(x / y) *y);
}

static void	get_z(double *x, double *y)
{
	while (*x > 2.0)
	{
		*x *= 0.5;
		*y += LN2;
	}
	while (*x < 0.5)
	{
		*x *= 2.0;
		*y -= LN2;
	}
}

double	ft_log(double x)
{
	double	y;
	double	res;
	double	term;
	unsigned long	i;

	if (x <= 0.0)
		return (0.0 / 0.0);
	else if (x == 1.0)
		return (0.0);
	y = 0.0;
	get_z(&x, &y);
	x -= 1.0;
	res = 0.0;
	term = x;
	i = 1;
	while (i < 20)
	{
		res += term / i;
		term *= -x;
		i++;
	}
	return (res + y);
}

double	ft_exp(double x)
{
	double	term;
	double	res;
	unsigned long	i;

	if (x > LNMAX)
		return (1.0 / 0.0);
	else if (x < LNMIN)
		return (0.0);
	if (x < 0.0)
		return (1.0 / ft_exp(-x));
	term = 1.0;
	res = 1.0;
	i = 1;
	while (i < 15)
	{
		term *= x / i;
		res += term;
		i++;
	}
	return (res);
}

double	ft_normalize_angle(double x)
{
	x = ft_mod(x, 2 * PI);
	if (x > PI)
		x -= 2 * PI;
	else if (x < -PI)
		x += 2 * PI;
	return (x);
}

double	ft_sin(double x)
{
	const double	x2 = x * x;

	x = ft_normalize_angle(x);
	if (x > HPI)
		return (-ft_sin(x - PI));
	else if (x < -HPI)
		return (-ft_sin(x + PI));
	return (x * (1.0 - x2 / 6.0 * (1.0 - x2 / 20.0 * (1.0 - x2 / 42.0))));
}

double	ft_cos(double x)
{
	const double	x2 = x * x;

	x = ft_normalize_angle(x);
	if (x > HPI)
		return (-ft_cos(x - PI));
	else if (x < -HPI)
		return (-ft_cos(x + PI));
	return (1.0 - x2 / 2.0 * (1.0 - x2 / 12.0 * (1.0 - x2 / 30.0)));
}

double	ft_tan(double x)
{
	const double	cos_x = ft_cos(x);

	if (ft_abs(cos_x) < 1e-10)
		return (0.0 / 0.0);
	return (ft_sin(x) / cos_x);
}

double	ft_atan(double x)
{
	double	res;
	unsigned long	i;

	if (x > 1.0)
		return (HPI - ft_atan(1.0 / x));
	else if (x < -1.0)
		return (-HPI - ft_atan(1.0 / x));
	else if (x > 0.5 || x < -0.5)
		return (x / (1.0 + 0.28125 * x * x));
	res = 0.0;
	i = 0;
	while (i < 10)
	{
		res += ft_pow(-1, i) * ft_pow(x, 2 * i + 1) / (2 * i + 1);
		i++;
	}
	return (res);
}

double	ft_asin(double x)
{
	if (x < -1.0 || x > 1.0)
		return (0.0 / 0.0);
	else if (x == 1.0)
		return (HPI);
	else if (x == -1.0)
		return (-HPI);
	return (ft_atan(x / ft_sqrt(1 - x * x)));
}

double	ft_argcos(double x)
{
	if (x < -1.0 || x > 1.0)
		return (0.0 / 0.0);
	else if (x == 1.0)
		return (0.0);
	else if (x == -1.0)
		return (PI);
	else if (x == 0.0)
		return (HPI);
	return (PI * (x < 0.0) + ft_atan(ft_sqrt(1 - x * x) / x));
}

double	ft_sinh(double x)
{
	const double	exp_x = ft_exp(x);

	return ((exp_x - 1.0 / exp_x) * 0.5);
}

double	ft_cosh(double x)
{
	const double	exp_x = ft_exp(x);

	return ((exp_x + 1.0 / exp_x) * 0.5);
}

double	ft_tanh(double x)
{
	const double	cosh_x = ft_cosh(x);

	if (cosh_x == 0.0)
		return (0.0 / 0.0);
	return (ft_sinh(x) / cosh_x);
}

double	ft_atan2(double y, double x)
{
	if (x > 0.0)
		return (ft_atan(y / x));
	else if (x < 0.0 && y >= 0.0)
		return (ft_atan(y / x) + PI);
	else if (x < 0.0 && y < 0.0)
		return (ft_atan(y / x) - PI);
	else if (x == 0.0 && y > 0.0)
		return (HPI);
	else if (x == 0.0 && y < 0.0)
		return (-HPI);
	return (0.0 / 0.0);
}

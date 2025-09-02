/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 23:51:25 by abidolet          #+#    #+#             */
/*   Updated: 2025/07/04 23:36:19 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_H
# define MATH_H

# define PI		3.14159265358979323846
# define HPI	1.57079632679489661923
# define QPI	0.78539816339744830962
# define LN2	0.69314718055994530942

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

double			ft_abs(double n);
double			ft_clamp(double n, double min, double max);
unsigned long	ft_factorial(unsigned long n);
double			ft_max(double a, double b);
double			ft_min(double a, double b);
double			ft_pow(double base, double exp);
double			ft_sqrt(double n);
long long		ft_round(double x);
long long		ft_floor(double x);
long long		ft_ceil(double x);
long long		ft_trunc(double x);
long long		ft_round_even(double x);
double			ft_exp(double x);
double			ft_log(double x);
t_vec3			ft_vec3_addv(const t_vec3 v1, const t_vec3 v2);
t_vec3			ft_vec3_subv(const t_vec3 v1, const t_vec3 v2);
t_vec3			ft_vec3_mulv(const t_vec3 v1, const t_vec3 v2);
t_vec3			ft_vec3_divv(const t_vec3 v1, const t_vec3 v2);
t_vec3			ft_vec3_addd(const t_vec3 v, double d);
t_vec3			ft_vec3_subd(const t_vec3 v, double d);
t_vec3			ft_vec3_muld(const t_vec3 v, double d);
t_vec3			ft_vec3_divd(const t_vec3 v, double d);

#endif

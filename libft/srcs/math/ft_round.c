/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:55:15 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/11 00:05:47 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

inline long long	ft_round(double x)
{
	return (x - 0.5 + (x >= 0));
}

inline long long	ft_floor(double x)
{
	return (x - !(x >= 0 || x == (long long)x));
}

inline long long	ft_ceil(double x)
{
	return (x + (x >= 0 && x != (long long)x));
}

inline long long	ft_trunc(double x)
{
	return (x - (x >= 0 && x != (long long)x) + !(x < 0 || x == (long long)x));
}

long long	ft_round_even(double x)
{
	if (x >= 0)
	{
		if (x - ft_floor(x) < 0.5)
			return (ft_floor(x));
		else if (x - ft_floor(x) > 0.5)
			return (ft_ceil(x));
		else
			return (ft_floor(x) + ((int)ft_floor(x) % 2));
	}
	else
	{
		if (x - ft_ceil(x) < 0.5)
			return (ft_ceil(x));
		else if (x - ft_ceil(x) > 0.5)
			return (ft_floor(x));
		else
			return (ft_ceil(x) + ((int)ft_ceil(x) % 2));
	}
}

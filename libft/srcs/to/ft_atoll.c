/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 20:47:41 by abidolet          #+#    #+#             */
/*   Updated: 2025/07/06 16:37:21 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/is.h"
#include "libft/limits.h"

long long	ft_atoll(const char *nptr)
{
	long long	res;
	int			sign;
	int			digit;

	if (!nptr)
		return (-1);
	res = 0;
	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			sign = -1;
	while (ft_isdigit(*nptr))
	{
		digit = *nptr++ - '0';
		if (sign == 1 && (res > LLONG_MAX / 10
				|| (res == LLONG_MAX / 10 && digit > LLONG_MAX % 10)))
			return (-1);
		else if (sign == -1 && (res > (LLONG_MAX / 10)
				|| (res == (LLONG_MAX / 10) && digit == 9)))
			return (-1);
		res = res * 10 + digit;
	}
	return (res * sign);
}

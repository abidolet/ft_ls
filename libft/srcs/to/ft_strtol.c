/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:41:13 by abidolet          #+#    #+#             */
/*   Updated: 2025/07/06 16:37:21 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/is.h"

long	ft_strtol(const char *nptr, char **endptr, int base)
{
	long long	res;
	int			sign;

	if (!nptr || !endptr || base < 2 || base > 36)
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
		res = res * base + *nptr++ - '0';
		if (res * sign != (long)(res * sign))
			return (-1);
	}
	return (res * sign);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:41:19 by abidolet          #+#    #+#             */
/*   Updated: 2025/07/06 16:37:21 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/is.h"
#include "limits.h"

int	ft_strtoi(const char *nptr, char **endptr, int base)
{
	long long	res;
	int			sign;

	if (!nptr || base < 2 || base > 36)
		return (0);
	endptr = (char **)&nptr;
	res = 0;
	sign = 1;
	while (ft_isspace(**endptr))
		(*endptr)++;
	sign = 1;
	if (**endptr == '+' || **endptr == '-')
		if (**endptr++ == '-')
			sign = -1;
	res = 0;
	while (ft_isxdigit(**endptr))
	{
		res *= base;
		if (ft_isdigit(**endptr))
			res += **endptr - '0';
		else
			res += **endptr - ('A' + (ft_islower(**endptr)) * 32) + 10;
		if (res * sign > LONG_MIN || res * sign < LONG_MAX)
			return (-1);
		(*endptr)++;
	}
	return (res * sign);
}

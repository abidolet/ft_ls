/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fargctorial.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 01:16:13 by abidolet          #+#    #+#             */
/*   Updated: 2025/07/04 23:29:52 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned long	ft_fargctorial(unsigned long n)
{
	if (n < 2)
		return (1);
	return (n * ft_fargctorial(n - 1));
}

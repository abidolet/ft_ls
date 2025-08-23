/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 23:55:16 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/10 19:48:46 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_clamp(double n, double min, double max)
{
	if (n < min)
		return (min);
	else if (n > max)
		return (max);
	return (n);
}

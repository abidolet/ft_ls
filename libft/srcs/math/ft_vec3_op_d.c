/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3_op_d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:44:27 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/11 09:55:36 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/math.h"

inline t_vec3	ft_vec3_addd(const t_vec3 v, double d)
{
	return ((t_vec3){v.x + d, v.y + d, v.z + d});
}

inline t_vec3	ft_vec3_subd(const t_vec3 v, double d)
{
	return ((t_vec3){v.x - d, v.y - d, v.z - d});
}

inline t_vec3	ft_vec3_muld(const t_vec3 v, double d)
{
	return ((t_vec3){v.x * d, v.y * d, v.z * d});
}

inline t_vec3	ft_vec3_divd(const t_vec3 v, double d)
{
	return ((t_vec3){v.x / d, v.y / d, v.z / d});
}

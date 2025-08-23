/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3_op_vec3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:03:09 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/11 09:55:22 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/math.h"

inline t_vec3	ft_vec3_addv(const t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

inline t_vec3	ft_vec3_subv(const t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}

inline t_vec3	ft_vec3_mulv(const t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){v1.x * v2.x, v1.y * v2.y, v1.z * v2.z});
}

inline t_vec3	ft_vec3_divv(const t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){v1.x / v2.x, v1.y / v2.y, v1.z / v2.z});
}

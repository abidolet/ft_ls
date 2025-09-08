/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 20:06:52 by abidolet          #+#    #+#             */
/*   Updated: 2025/09/04 22:12:51 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/mem.h"
#include <stdlib.h>

void	*ft_realloc(void *ptr, size_t size)
{
	void	*res;

	if (!ptr)
		return (malloc(size));
	else if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	res = malloc(size);
	if (!res)
		return (NULL);
	ft_memcpy(res, ptr, size);
	free(ptr);
	return (res);
}

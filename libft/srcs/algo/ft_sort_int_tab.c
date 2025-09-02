/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 00:57:08 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/10 16:03:03 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/algo.h"

void	sort_int_tab(int *tab, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;
	int				*min;

	if (tab && size > 1)
	{
		i = 0;
		while (i < size)
		{
			j = i;
			min = &tab[i];
			while (++j < size)
				if (*min > tab[j])
					min = &tab[j++];
			if (min != &tab[i])
				ft_swap((void **)min, (void **)&tab[i]);
			i++;
		}
	}
}

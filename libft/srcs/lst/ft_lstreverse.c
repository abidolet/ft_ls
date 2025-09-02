/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstreverse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 23:40:52 by abidolet          #+#    #+#             */
/*   Updated: 2025/07/05 11:26:25 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/lst.h"

void	ft_lstreverse(t_list **lst)
{
	t_list	*prev;
	t_list	*current;
	t_list	*next;

	if (lst && *lst)
	{
		prev = 0x0;
		current = *lst;
		while (current != 0x0)
		{
			next = current->next;
			current->next = prev;
			prev = current;
			current = next;
		}
		*lst = prev;
	}
}

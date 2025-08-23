/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 01:00:17 by abidolet          #+#    #+#             */
/*   Updated: 2025/07/05 01:24:01 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/lst.h"

t_list	*ft_lstsort(t_list *lst, int (*cmp)(void *, void *))
{
	t_list	*res;
	t_list	*current;
	t_list	**insert;

	if (!lst || !cmp)
		return (lst);
	res = 0x0;
	while (lst)
	{
		current = lst;
		lst = lst->next;
		insert = &res;
		while (*insert && cmp(current->content, (*insert)->content) > 0)
			insert = &(*insert)->next;
		current->next = *insert;
		*insert = current;
	}
	return (res);
}

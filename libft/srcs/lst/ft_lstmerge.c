/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmerge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 00:00:00 by abidolet          #+#    #+#             */
/*   Updated: 2025/09/03 00:00:00 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/lst.h"

t_list *ft_lstmerge(t_list *a, t_list *b)
{
    if (!a)
        return (b);
    ft_lstlast(a)->next = b;
    return (a);
}

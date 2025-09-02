/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:51:52 by abidolet          #+#    #+#             */
/*   Updated: 2025/02/15 21:51:52 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*res;

	res = 0x0;
	while (s && *s)
		if (*s++ == (char)c)
			res = (char *)(s - 1);
	if (s && *s == (char)c)
		return ((char *)s);
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 22:16:16 by abidolet          #+#    #+#             */
/*   Updated: 2025/07/04 08:27:27 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TO_H
# define TO_H

int			ft_atoi_base(const char *str, int str_base);
int			ft_atoi(const char *nptr);
long		ft_atol(const char *nptr);
long long	ft_atoll(const char *nptr);
double		ft_atod(const char *nptr);
char		*ft_itoa(int n);
int			ft_strtoi(const char *nptr, char **end, int base);
long		ft_strtol(const char *nptr, char **endptr, int base);
int			ft_tolower(int c);
int			ft_toupper(int c);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:23:44 by abidolet          #+#    #+#             */
/*   Updated: 2025/07/04 23:33:24 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/bool.h"

typedef struct s_flags
{
	BOOL			minus;
	BOOL			zero;
	BOOL			dot;
	unsigned long	width;
	BOOL			hash;
	BOOL			space;
	BOOL			plus;
	unsigned long	precision;
}	t_flags;

int	ft_printf(const char *str, ...);
int	ft_dprintf(int fd, const char *str, ...);
int	ft_putchar_fd(char c, int fd);
int	ft_putstr_fd(char *s, int fd);
int	ft_putnbr_fd(long n, int fd);
int	ft_puthex_fd(unsigned long n, char c, int fd);
int	ft_putptr_fd(void *ptr, int fd);

#endif

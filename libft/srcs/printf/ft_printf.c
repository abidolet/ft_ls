/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 00:38:45 by abidolet          #+#    #+#             */
/*   Updated: 2025/07/06 16:37:21 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_printf.h"
#include <stdarg.h>
#include "libft/is.h"
#include "libft/str.h"
#include "libft/mem.h"
#include "libft/to.h"
#include <unistd.h>

int	puthex_len(unsigned long long n)
{
	if (n < 16)
		return (1);
	return (1 + puthex_len(n / 16));
}

static int	puthex_flags(unsigned int n, char c, int fd, t_flags *flags)
{
	unsigned long	res;
	unsigned long	num_len;
	unsigned long	precision_len;
	unsigned long	total_len;
	unsigned long	padding;

	res = 0;
	if (n == 0 && flags->dot && flags->precision == 0)
	{
		while (flags->width-- > 0)
			res += ft_putchar_fd(' ', fd);
		return (res);
	}
	num_len = puthex_len(n);
	precision_len = 0;
	if (flags->precision > num_len)
		precision_len = flags->precision - num_len;
	total_len = num_len + (flags->hash && n != 0) * 2 + precision_len;
	if (!flags->minus && total_len < flags->width)
	{
		padding = flags->width - total_len;
		while (padding-- > 0)
		{
			if (flags->zero && !flags->dot && !flags->minus)
				res += ft_putchar_fd('0', fd);
			else
				res += ft_putchar_fd(' ', fd);
		}
	}
	if (flags->hash && n != 0)
		res += ft_putchar_fd('0', fd) + ft_putchar_fd(c, fd);
	while (precision_len-- > 0)
		res += ft_putchar_fd('0', fd);
	if (!(n == 0 && flags->dot && flags->precision == 0))
		res += ft_puthex_fd(n, c, fd);
	if (flags->minus && total_len < flags->width)
		while (res < flags->width)
			res += ft_putchar_fd(' ', fd);
	return (res);
}

static unsigned long	nbrlen(long n)
{
	if (n < 0)
		return (1 + nbrlen(-n));
	else if (n < 10)
		return (1);
	else
		return (1 + nbrlen(n / 10));
}

static int	putnbr_flags(long n, int fd, t_flags *flags)
{
	int		res;
	unsigned long	num_len;
	unsigned long	total_len;
	_Bool	sign_len;
	unsigned long	padding_needed;
	unsigned long	i;

	res = 0;
	num_len = nbrlen(n);
	sign_len = (n < 0 || flags->plus || flags->space);
	if (n == 0 && flags->dot && flags->precision == 0)
	{
		while (flags->width-- > 0)
			res += ft_putchar_fd(' ', fd);
		return (res);
	}
	total_len = num_len;
	if (flags->precision > num_len - (n < 0))
		total_len = flags->precision + (n < 0);
	total_len += sign_len - (n < 0);
	if ((flags->zero && !flags->dot && !flags->minus)
		&& (n < 0 || flags->plus || flags->space))
	{
		if (n < 0)
			res += ft_putchar_fd('-', fd);
		else if (flags->plus)
			res += ft_putchar_fd('+', fd);
		else if (flags->space)
			res += ft_putchar_fd(' ', fd);
		sign_len = 0;
	}
	if (!flags->minus)
	{
		padding_needed = 0;
		if (flags->width > total_len)
			padding_needed = flags->width - total_len;
		i = 0;
		while (i < padding_needed)
		{
			if (flags->zero && !flags->dot && !flags->minus)
				res += ft_putchar_fd('0', fd);
			else
				res += ft_putchar_fd(' ', fd);
			i++;
		}
	}
	if (sign_len > 0)
	{
		if (n < 0)
			res += ft_putchar_fd('-', fd);
		else if (flags->plus)
			res += ft_putchar_fd('+', fd);
		else if (flags->space)
			res += ft_putchar_fd(' ', fd);
	}
	while ((num_len++ - (n < 0)) < flags->precision)
		res += ft_putchar_fd('0', fd);
	if (!(n == 0 && flags->dot && flags->precision == 0))
	{
		if (n < 0)
			n = -n;
		res += ft_putnbr_fd(n, fd);
	}
	if (flags->minus)
	{
		padding_needed = 0;
		if (flags->width > total_len)
			padding_needed = flags->width - total_len;
		i = -1;
		while (++i < padding_needed)
			res += ft_putchar_fd(' ', fd);
	}
	return (res);
}

static int	putstr_flags(char *s, int fd, t_flags *flags)
{
	unsigned long	res;
	unsigned long	tmp;

	res = 0;
	tmp = 0;
	if (s)
		tmp = ft_strlen(s);
	else if (!flags->dot || flags->precision >= 6)
		tmp = 6;
	if (flags->dot && flags->precision < tmp)
		tmp = flags->precision;
	if (!flags->minus)
		while (flags->width > res + tmp)
			res += ft_putchar_fd(' ', fd);
	if (s)
		res += write(fd, s, tmp);
	else if (!flags->dot || flags->precision >= 6)
		res += write(fd, "(null)", tmp);
	if (flags->minus)
		while (flags->width > res)
			res += ft_putchar_fd(' ', fd);
	return (res);
}

static int	putchar_flags(int c, int fd, t_flags *flags)
{
	unsigned long	res;

	res = 0;
	if (!flags->minus)
		while (flags->width-- > 1)
			res += ft_putchar_fd(' ', fd);
	res += ft_putchar_fd(c, fd);
	if (flags->minus)
		while (flags->width > res)
			res += ft_putchar_fd(' ', fd);
	return (res);
}

static int	putptr_flags(void *ptr, int fd, t_flags *flags)
{
	unsigned long	res;
	unsigned long	tmp;

	res = 0;
	tmp = puthex_len((unsigned long long)ptr) + 2;
	if (!ptr)
		tmp = 5;
	if (!flags->minus)
		while (flags->width-- > tmp)
			res += ft_putchar_fd(' ', fd);
	if (!ptr)
		return (res + ft_putstr_fd("(nil)", fd));
	res += write(fd, "0x", 2) + ft_puthex_fd((unsigned long)ptr, 'x', fd);
	if (flags->minus)
		while (flags->width > res)
			res += ft_putchar_fd(' ', fd);
	return (res);
}

static int	switch_printf(char c, va_list arg, int fd, t_flags *flags)
{
	if (c == 'c')
		return (putchar_flags(va_arg(arg, int), fd, flags));
	else if (c == 's')
		return (putstr_flags(va_arg(arg, char *), fd, flags));
	else if (c == 'p')
		return (putptr_flags(va_arg(arg, void *), fd, flags));
	else if (c == 'd' || c == 'i')
		return (putnbr_flags(va_arg(arg, int), fd, flags));
	else if (c == 'u')
		return (putnbr_flags(va_arg(arg, unsigned int), fd, flags));
	else if (c == 'x' || c == 'X')
		return (puthex_flags(va_arg(arg, unsigned int), c, fd, flags));
	else if (c == '%')
		return (ft_putchar_fd('%', fd));
	return (0);
}

static char	*parse_flags(char *s, t_flags *flags)
{
	while (*s)
	{
		if (*s == '-')
			flags->minus = TRUE;
		else if (*s == '0')
			flags->zero = TRUE;
		else if (*s == '.')
		{
			flags->dot = TRUE;
			flags->precision = ft_strtoi(++s, &s, 10);
			continue ;
		}
		else if (*s == '#')
			flags->hash = TRUE;
		else if (*s == ' ')
			flags->space = TRUE;
		else if (*s == '+')
			flags->plus = TRUE;
		else if (ft_isdigit(*s))
		{
			flags->width = ft_strtoi(s, &s, 10);
			continue ;
		}
		else
			break ;
		s++;
	}
	return (s);
}

int	ft_printf(const char *s, ...)
{
	va_list	arg;
	int		res;
	char	*tmp;
	t_flags	flags;

	if (!s)
		return (-1);
	va_start(arg, s);
	res = 0;
	while (*s)
	{
		tmp = ft_strchr(s, '%');
		if (!tmp)
		{
			res += ft_putstr_fd((char *)s, 1);
			break ;
		}
		res += write(1, s, tmp - s);
		ft_bzero(&flags, sizeof(t_flags));
		s = parse_flags(tmp + 1, &flags);
		res += switch_printf(*s++, arg, 1, &flags);
	}
	va_end(arg);
	return (res);
}

int	ft_dprintf(int fd, const char *s, ...)
{
	va_list	arg;
	int		res;
	char	*tmp;
	t_flags	flags;

	if (!s)
		return (-1);
	va_start(arg, s);
	res = 0;
	while (*s)
	{
		tmp = ft_strchr(s, '%');
		if (!tmp)
		{
			res += ft_putstr_fd((char *)s, fd);
			break ;
		}
		res += write(fd, s, tmp - s);
		ft_bzero(&flags, sizeof(t_flags));
		s = parse_flags(tmp + 1, &flags);
		res += switch_printf(*s++, arg, fd, &flags);
	}
	va_end(arg);
	return (res);
}

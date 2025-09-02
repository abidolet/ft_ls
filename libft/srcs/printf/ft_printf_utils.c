/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 10:33:55 by abidolet          #+#    #+#             */
/*   Updated: 2025/07/04 23:22:10 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}

int	ft_putstr_fd(char *s, int fd)
{
	unsigned long	size;

	size = 0;
	while (s[size])
		size++;
	return (write(fd, s, size));
}

int	ft_putnbr_fd(long long n, int fd)
{
	if (n < 0)
		return (ft_putchar_fd('-', fd) + ft_putnbr_fd(-n, fd));
	else if (n < 10)
		return (ft_putchar_fd(n + '0', fd));
	return (ft_putnbr_fd(n / 10, fd) + ft_putchar_fd(n % 10 + '0', fd));
}

int	ft_puthex_fd(unsigned long long n, char c, int fd)
{
	if (n < 10)
		return (ft_putchar_fd(n + '0', fd));
	else if (n < 16)
		return (ft_putchar_fd(n - 10 + c - ('x' - 'a'), fd));
	return (ft_puthex_fd(n / 16, c, fd) + ft_puthex_fd(n % 16, c, fd));
}

int	ft_putptr_fd(void *ptr, int fd)
{
	if (!ptr)
		return (ft_putstr_fd("(nil)", fd));
	return (ft_putstr_fd("0x", fd) + ft_puthex_fd((unsigned long)ptr, 'x', fd));
}

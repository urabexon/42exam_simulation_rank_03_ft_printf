/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:23:17 by hurabe            #+#    #+#             */
/*   Updated: 2024/07/21 19:30:21 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> // for malloc, free
#include <unistd.h> // for write
#include <stdarg.h> // for va_start, va_arg, va_copy, va_end
#include <stdio.h> // for real printf

int	ft_printf_write(int c, int i)
{
	i++;
	write(1, &c, 1);
	return (i);
}

int	ft_found_x(size_t x, int i)
{
	unsigned int	u;
	
	u = (unsigned int)x;
	if (u == 0)
		i = ft_printf_write('0', i);
	else if (u >= 16) // 0123456789abcdef
	{
		i = ft_found_x(u / 16, i);
		i = ft_found_x(u % 16, i);
	}
	else
	{
		if (u <= 9)
			i = ft_printf_write(u + '0', i);
		else
			i = ft_printf_write(u + 'a' - 10, i);
	}
	return (i);
}

int	ft_found_d(int d, int i)
{
	if (d == -2147483648)
	{
		write(1, "-2147483648", 11);
		i = i + 11;
	}
	if (d < 0)
	{
		i = ft_printf_write('-', i);
		i = ft_found_d(-d, i);
	}
	else if (d >= 0 && d < 10)
		i = ft_printf_write(d + '0', i);
	else
	{
		i = ft_found_d(d / 10, i);
		i = ft_printf_write(d % 10 + '0', i);
	}
	return (i);
}

int	ft_found_s(char	*s, int i)
{
	if (!s)
		i = ft_found_s("(null)", i);
	else
	{
		while (*s)
		{
			write(1, &(*s), 1);
			i++;
			s++;
		}
	}
	return (i);
}

int	ft_next_percent(const char *format, va_list args, int i, int j)
{
	if (format[j] == 's')
		ft_found_s(va_arg(args, char *), i);
	if (format[j] == 'd')
		ft_found_d(va_arg(args, int), i);
	if (format[j] == 'x')
		ft_found_x(va_arg(args, size_t), i);
	return (i);
}

int	ft_printf(const	char *format, ...)
{
	va_list	args;
	int		i;
	int		j;

	i = 0;
	j = 0;
	va_start(args, format);
	while (format[j])
	{
		if (format[j] == '%')
			i = ft_next_percent(format, args, i, ++j);
		else
		{
			i++;
			write(1, &format[j], 1);
		}
		j++;
	}
	va_end(args);
	return (i);
}
/*
int	main(void)
{
	int	i;

	// ft_printf("MIN number: %i", INT32_MIN);
	// printf("MIN number: %i", INT32_MIN);
	
	i = ft_printf("me --> Hello,42!\ns: %s, d: %d, x: %x\n", NULL, 42, 42424242);
	printf("i: %i\n\n", i);
	i = printf("real --> Hello,42!\ns: %s, d: %d, x: %x\n", NULL, 42, 42424242);
	printf("i: %i\n\n", i);
	// i = printf("hi\n");
	// printf("i: %i\n", i);

	// printf("%s\n", "toto");
	// printf("Magic %s is %d", "number", 42);
	// printf("Hexadecimal for %d is %x\n", 42, 42);
	return (0);
}
*/
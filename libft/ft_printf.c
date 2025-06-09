/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:35:15 by abouchat          #+#    #+#             */
/*   Updated: 2024/10/21 16:16:27 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_next_letter(char c, va_list args)
{
	int	count;

	count = 0;
	if (c == 'c')
		count = ft_putchar_args((va_arg(args, int)));
	else if (c == 's')
		count = ft_putstr_args((va_arg(args, char *)));
	else if (c == 'd' || c == 'i')
		count = ft_putnbr_args((va_arg(args, int)));
	else if (c == '%')
		count = ft_putchar_args('%');
	else if (c == 'x')
		count = ft_print_hex_args((va_arg(args, unsigned int)), 0);
	else if (c == 'X')
		count = ft_print_hex_args((va_arg(args, unsigned int)), 1);
	else if (c == 'p')
		count = ft_putaddr_args((va_arg(args, void *)));
	else if (c == 'u')
		count = ft_putunsign_args((va_arg(args, unsigned int)));
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	va_list	args;
	int		len;

	if (!format)
		return (-1);
	len = 0;
	va_start(args, format);
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			len += check_next_letter(format[i + 1], args);
			i++;
		}
		else
			len += ft_putchar_args(format[i]);
		i++;
	}
	va_end(args);
	return (len);
}

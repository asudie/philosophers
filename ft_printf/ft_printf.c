/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmolnya < asmolnya@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:29:15 by asmolnya          #+#    #+#             */
/*   Updated: 2023/10/22 15:15:31 by asmolnya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	va_start(ap, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
			count += print_format(*(++format), ap);
		else
			count += write(1, format, 1);
		++format;
	}
	va_end(ap);
	return (count);
}

int	print_format(char sp, va_list ap)
{
	int	count;

	count = 0;
	if (sp == 'c')
		count += print_char(va_arg(ap, int));
	else if (sp == 's')
		count += print_str(va_arg(ap, char *));
	else if (sp == 'd' || sp == 'i')
		count += print_digit((long)va_arg(ap, int), 10, 0);
	else if (sp == 'u')
		count += case_u(ap);
	else if (sp == 'x')
		count += print_digit((long)va_arg(ap, unsigned int), 16, 0);
	else if (sp == 'X')
		count += print_digit((long)va_arg(ap, unsigned int), 16, 1);
	else if (sp == 'p')
		count += print_pointer(ap);
	else
		count += write(1, "%", 1);
	return (count);
}

int	print_digit(long n, int base, int flag)
{
	int		count;
	char	*symb;

	count = 0;
	symb = "0123456789abcdef";
	if (flag)
	{
		symb = "0123456789ABCDEF";
	}
	if (n < 0)
	{
		write(1, "-", 1);
		count += print_digit(-n, base, flag) + 1;
	}
	else if (n < base)
	{
		return (print_char(symb[n]));
	}
	else
	{
		count += print_digit(n / base, base, flag);
		return (count + print_digit(n % base, base, flag));
	}
	return (count);
}
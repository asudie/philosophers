/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmolnya < asmolnya@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:42:00 by asmolnya          #+#    #+#             */
/*   Updated: 2023/10/22 15:15:24 by asmolnya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stddef.h>
#include <stdint.h>

int	case_u(va_list ap)
{
	long int	temp;

	temp = va_arg(ap, int);
	if (temp < 0)
		temp = UINT32_MAX + temp + 1;
	return (print_digit(temp, 10, 0));
}

int	print_pointer(va_list ap)
{
	int			count;
	void		*temp;

	count = 0;
	temp = (va_arg(ap, void *));
	count += print_str("0x");
	if ((long int)temp == 0)
	{
		print_str("0");
		count += 1;
	}
	else if ((unsigned long int)temp > (unsigned long int)INT64_MAX)
	{
		temp = (void *)(UINT64_MAX + (unsigned long int)temp + 1);
		count += ptr_digit((unsigned long int)temp);
	}
	else
		count += print_digit((long int)temp, 16, 0);
	return (count);
}

int	ptr_digit(unsigned long int n)
{
	int		count;
	char	*symb;

	count = 0;
	symb = "0123456789abcdef";
	if (n < 16)
	{
		return (print_char(symb[n]));
	}
	else
	{
		count += ptr_digit(n / 16);
		return (count + ptr_digit(n % 16));
	}
	return (count);
}

int	print_char(int c)
{
	return (write(1, &c, 1));
}

int	print_str(char *str)
{
	int	count;

	if (str == NULL)
		str = "(null)";
	count = 0;
	while (*str)
	{
		print_char((int)*str);
		count++;
		str++;
	}
	return (count);
}
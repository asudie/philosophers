/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmolnya < asmolnya@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:29:27 by asmolnya          #+#    #+#             */
/*   Updated: 2023/10/22 14:23:32 by asmolnya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>

int	ft_printf(const char *format, ...);
int	print_format(char sp, va_list ap);
int	print_char(int c);
int	print_str(char *str);
int	print_digit(long n, int base, int flag);
int	case_u(va_list ap);
int	print_pointer(va_list ap);
int	ptr_digit(unsigned long int n);
#endif
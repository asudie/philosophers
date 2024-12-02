/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmolnya <asmolnya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 08:37:28 by asmolnya          #+#    #+#             */
/*   Updated: 2023/07/26 08:44:18 by asmolnya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*x;
	const unsigned char	*y;

	x = ((unsigned char *)dst);
	y = ((const unsigned char *)src);
	if (x == y)
		return (dst);
	else if (x > y)
	{
		y = y + len - 1;
		x = x + len - 1;
		while (len > 0)
		{
			*x = *y;
			x--;
			y--;
			len--;
		}
	}
	else
		dst = ft_memcpy(x, y, len);
	return (dst);
}

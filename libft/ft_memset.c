/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmolnya <asmolnya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 08:50:04 by asmolnya          #+#    #+#             */
/*   Updated: 2023/07/26 08:50:45 by asmolnya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*lhv;
	size_t			i;

	lhv = s;
	i = 0;
	while (i < n)
	{
		lhv[i] = c;
		i++;
	}
	return (lhv);
}

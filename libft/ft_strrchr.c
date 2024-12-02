/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmolnya <asmolnya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 08:05:56 by asmolnya          #+#    #+#             */
/*   Updated: 2023/07/26 08:09:43 by asmolnya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	x;

	i = 0;
	x = ((char)c);
	while (s[i] != '\0')
	{
		i++;
	}
	while (i > 0)
	{
		if (s[i] == x)
		{
			return (&((char *)s)[i]);
		}
		i--;
	}
	if (i == 0)
	{
		if (s[i] == x)
			return (&((char *)s)[i]);
	}
	return (0);
}

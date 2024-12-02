/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmolnya <asmolnya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 06:46:22 by asmolnya          #+#    #+#             */
/*   Updated: 2023/07/26 16:12:19 by asmolnya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*loop(char *res_b, char *t_l, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (res_b[i] && i < len)
	{
		j = 0;
		if (res_b[i] == t_l[j])
		{
			while (res_b[i] == t_l[j] && t_l[j] && i < len)
			{
				i++;
				j++;
			}
			if (j == ft_strlen(little))
				return (res_b + i - j);
			else if (j > 1)
				i--;
		}
		else
			i++;
	}
	return (NULL);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*res_b;
	char	*t_l;
	char	*res;

	res_b = (char *)big;
	t_l = (char *)little;
	if ((int)len < 0)
	{
		len = ft_strlen(res_b) + len;
	}
	if (little[0] == '\0')
		return (res_b);
	res = loop(res_b, t_l, little, len);
	if (res)
		return (res);
	return (NULL);
}

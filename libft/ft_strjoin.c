/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmolnya <asmolnya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 10:32:25 by asmolnya          #+#    #+#             */
/*   Updated: 2023/07/26 10:33:16 by asmolnya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*join(char const *s1, char const *s2, char *new_str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while ((size_t)i < ft_strlen(s1))
	{
		new_str[i] = s1[i];
		i++;
	}
	while ((size_t)j < ft_strlen(s2))
	{
		new_str[j + ft_strlen(s1)] = s2[j];
		j++;
	}
	new_str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (new_str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;

	new_str = malloc (sizeof (char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new_str)
		join(s1, s2, new_str);
	else
		new_str = 0;
	return (new_str);
}

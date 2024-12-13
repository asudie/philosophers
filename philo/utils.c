/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmolnya <asmolnya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 22:28:49 by asmolnya          #+#    #+#             */
/*   Updated: 2024/12/13 22:29:16 by asmolnya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(t_args *args)
{
	struct timeval	current_time;
	long			seconds;
	long			microsec;

	gettimeofday(&current_time, NULL);
	seconds = current_time.tv_sec - args->start_time.tv_sec;
	microsec = current_time.tv_usec - args->start_time.tv_usec;
	return ((seconds * 1000) + (microsec / 1000));
}

int	check_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit((int)str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_values(t_args *args)
{
	if (args->philos_num < 1 || args->philos_num > 200)
	{
		printf("Wrong number of philosophers!\n");
		return (1);
	}
	return (0);
}

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (check_line(argv[i]))
			return (1);
		i++;
	}
	return (0);
}

void	*handle_one(t_meal_info *info)
{
	usleep(info->args->time2die);
	return (NULL);
}

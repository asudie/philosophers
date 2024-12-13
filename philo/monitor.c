/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmolnya <asmolnya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 22:22:33 by asmolnya          #+#    #+#             */
/*   Updated: 2024/12/13 22:33:30 by asmolnya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_full(t_meal_info *info)
{
	int	i;

	i = 0;
	while (i < info->args->philos_num)
	{
		pthread_mutex_lock(&info[i].full_mutex);
		if (info[i].meal_count < info->args->times2eat)
		{
			pthread_mutex_unlock(&info[i].full_mutex);
			return (0);
		}
		pthread_mutex_unlock(&info[i].full_mutex);
		i++;
	}
	pthread_mutex_lock(&info->args->death_full_mutex);
	*info->args->full_stop = 1;
	pthread_mutex_unlock(&info->args->death_full_mutex);
	return (1);
}

void	handle_death(t_meal_info *info, int i, long current_time)
{
	pthread_mutex_lock(&info->args->print_lock);
	printf("%ld %d died\n", current_time, info[i].id);
	pthread_mutex_unlock(&info->args->print_lock);
	pthread_mutex_lock(&info->args->death_full_mutex);
	*info->args->philosopher_died = 1;
	pthread_mutex_unlock(&info->args->death_full_mutex);
}

int	check_philosopher(t_meal_info *info, int i)
{
	long	current_time;

	current_time = get_time_ms(info->args);
	pthread_mutex_lock(&info[i].meal_time_mutex);
	if (current_time - info[i].last_meal_time >= info->args->time2die)
	{
		handle_death(info, i, current_time);
		pthread_mutex_unlock(&info[i].meal_time_mutex);
		return (1);
	}
	pthread_mutex_unlock(&info[i].meal_time_mutex);
	return (0);
}

void	*monitor(void *arg)
{
	t_meal_info	*info;
	int			i;

	info = (t_meal_info *)arg;
	while (1)
	{
		i = 0;
		while (i < info->args->philos_num)
		{
			if (check_philosopher(info, i))
				return (NULL);
			i++;
		}
		if (info->args->times2eat > 0 && check_full(info))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

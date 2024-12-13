/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmolnya <asmolnya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 22:06:07 by asmolnya          #+#    #+#             */
/*   Updated: 2024/12/13 22:33:30 by asmolnya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	increment_meal_count(t_meal_info *info)
{
	pthread_mutex_lock(&info->full_mutex);
	info->meal_count++;
	pthread_mutex_unlock(&info->full_mutex);
}

int	check_termination(t_meal_info *info)
{
	int	terminated;

	terminated = 0;
	pthread_mutex_lock(&info->args->death_full_mutex);
	if (*info->args->philosopher_died || *info->args->full_stop)
		terminated = 1;
	pthread_mutex_unlock(&info->args->death_full_mutex);
	return (terminated);
}

void	*philosopher(void *arg)
{
	t_meal_info	*info;
	int			id;
	int			left_fork;
	int			right_fork;

	info = (t_meal_info *)arg;
	id = info->id;
	left_fork = id;
	right_fork = (id + 1) % info->args->philos_num;
	pthread_mutex_lock(&info->full_mutex);
	info->meal_count = 0;
	pthread_mutex_unlock(&info->full_mutex);
	if (info->args->philos_num == 1)
		return (handle_one(info));
	while (1)
	{
		if (check_termination(info))
			return (NULL);
		philosopher_eat(info, id, left_fork, right_fork);
		philosopher_sleep(info, id);
		philosopher_think(info, id);
	}
}

int	create_philos_and_forks(t_args *args)
{
	pthread_t	monitor_thread;
	int			death;
	int			full;

	death = 0;
	full = 0;
	args->philosopher_died = &death;
	args->full_stop = &full;
	if (init_resources(args) != 0)
		return (1);
	init_philosophers_and_forks(args);
	if (create_threads(args, &monitor_thread) != 0)
		return (1);
	join_threads(args, monitor_thread);
	cleanup_resources(args);
	return (0);
}

int	philos(t_args *args)
{
	gettimeofday(&args->start_time, NULL);
	return (create_philos_and_forks(args));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmolnya <asmolnya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 22:26:48 by asmolnya          #+#    #+#             */
/*   Updated: 2024/12/13 22:30:13 by asmolnya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_meal_info *info, int left_fork, int right_fork)
{
	if (info->id % 2 == 0)
	{
		pthread_mutex_lock(&info->args->forks[left_fork]);
		pthread_mutex_lock(&info->args->forks[right_fork]);
	}
	else
	{
		pthread_mutex_lock(&info->args->forks[right_fork]);
		pthread_mutex_lock(&info->args->forks[left_fork]);
	}
}

void	release_forks(t_meal_info *info, int left_fork, int right_fork)
{
	pthread_mutex_unlock(&info->args->forks[right_fork]);
	pthread_mutex_unlock(&info->args->forks[left_fork]);
}

void	philosopher_eat(t_meal_info *info, int id, int left_fork,
		int right_fork)
{
	take_forks(info, left_fork, right_fork);
	if (check_termination(info))
	{
		release_forks(info, left_fork, right_fork);
		return ;
	}
	increment_meal_count(info);
	pthread_mutex_lock(&info->args->print_lock);
	printf("%ld %d is eating\n", get_time_ms(info->args), id);
	pthread_mutex_unlock(&info->args->print_lock);
	pthread_mutex_lock(&info->meal_time_mutex);
	info->last_meal_time = get_time_ms(info->args);
	pthread_mutex_unlock(&info->meal_time_mutex);
	usleep(1000 * info->args->time2eat);
	release_forks(info, left_fork, right_fork);
}

void	philosopher_sleep(t_meal_info *info, int id)
{
	if (check_termination(info))
		return ;
	pthread_mutex_lock(&info->args->print_lock);
	printf("%ld %d is sleeping\n", get_time_ms(info->args), id);
	pthread_mutex_unlock(&info->args->print_lock);
	usleep(1000 * info->args->time2sleep);
}

void	philosopher_think(t_meal_info *info, int id)
{
	if (check_termination(info))
		return ;
	pthread_mutex_lock(&info->args->print_lock);
	printf("%ld %d is thinking\n", get_time_ms(info->args), id);
	pthread_mutex_unlock(&info->args->print_lock);
	usleep(1000);
}

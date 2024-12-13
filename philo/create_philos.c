/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmolnya <asmolnya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 22:24:03 by asmolnya          #+#    #+#             */
/*   Updated: 2024/12/13 22:33:30 by asmolnya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philosophers_and_forks(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->philos_num)
	{
		pthread_mutex_init(&args->forks[i], NULL);
		pthread_mutex_init(&args->info[i].meal_time_mutex, NULL);
		pthread_mutex_init(&args->info[i].full_mutex, NULL);
		args->info[i].args = args;
		args->info[i].id = i;
		args->info[i].last_meal_time = get_time_ms(args);
		i++;
	}
}

int	create_threads(t_args *args, pthread_t *monitor_thread)
{
	int	i;

	i = 0;
	while (i < args->philos_num)
	{
		if (pthread_create(&args->philos[i], NULL, philosopher,
				&args->info[i]) != 0)
		{
			printf("Failed to create philosopher\n");
			return (1);
		}
		i++;
	}
	if (pthread_create(monitor_thread, NULL, monitor, args->info) != 0)
	{
		printf("Failed to create monitor thread\n");
		return (1);
	}
	return (0);
}

void	join_threads(t_args *args, pthread_t monitor_thread)
{
	int	i;

	i = 0;
	while (i < args->philos_num)
	{
		pthread_join(args->philos[i], NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
}

void	cleanup_resources(t_args *args)
{
	int	i;

	pthread_mutex_destroy(&args->print_lock);
	i = 0;
	while (i < args->philos_num)
	{
		pthread_mutex_destroy(&args->forks[i]);
		pthread_mutex_destroy(&args->info[i].meal_time_mutex);
		pthread_mutex_destroy(&args->info[i].full_mutex);
		i++;
	}
	free(args->forks);
	free(args->philos);
	free(args->info);
}

int	init_resources(t_args *args)
{
	args->forks = malloc(sizeof(pthread_mutex_t) * args->philos_num);
	args->philos = malloc(sizeof(pthread_t) * args->philos_num);
	args->info = malloc(sizeof(t_meal_info) * args->philos_num);
	pthread_mutex_init(&args->print_lock, NULL);
	pthread_mutex_init(&args->death_full_mutex, NULL);
	if (!args->forks || !args->philos || !args->info)
	{
		printf("Failed to allocate memory for forks, info, or philos\n");
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmolnya <asmolnya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 22:32:14 by asmolnya          #+#    #+#             */
/*   Updated: 2024/12/13 22:33:30 by asmolnya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../libft/libft.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_args	t_args;

typedef struct s_meal_info
{
	long				last_meal_time;
	pthread_mutex_t		meal_time_mutex;
	int					id;
	int					meal_count;
	pthread_mutex_t		full_mutex;
	t_args				*args;
}						t_meal_info;

typedef struct s_args
{
	int					philos_num;
	int					time2die;
	int					time2eat;
	int					time2sleep;
	int					times2eat;
	pthread_mutex_t		*forks;
	pthread_t			*philos;
	t_meal_info			*info;
	int					*philosopher_died;
	int					*full_stop;
	pthread_mutex_t		death_full_mutex;
	struct timeval		start_time;
	pthread_mutex_t		print_lock;
}						t_args;

int						philos(t_args *args);
int						create_philos_and_forks(t_args *args);
void					*philosopher(void *arg);
long					get_time_ms(t_args *args);
void					*monitor(void *arg);
int						check_full(t_meal_info *info);
void					*handle_one(t_meal_info *info);
int						check_args(int argc, char **argv);
int						check_line(char *str);
int						check_values(t_args *args);
int						check_philosopher(t_meal_info *info, int i);
void					handle_death(t_meal_info *info, int i,
							long current_time);
void					cleanup_resources(t_args *args);
void					join_threads(t_args *args, pthread_t monitor_thread);
int						create_threads(t_args *args, pthread_t *monitor_thread);
void					init_philosophers_and_forks(t_args *args);
void					philosopher_think(t_meal_info *info, int id);
void					philosopher_sleep(t_meal_info *info, int id);
void					philosopher_eat(t_meal_info *info, int id,
							int left_fork, int right_fork);
void					release_forks(t_meal_info *info, int left_fork,
							int right_fork);
void					take_forks(t_meal_info *info, int left_fork,
							int right_fork);
int						check_termination(t_meal_info *info);
void					increment_meal_count(t_meal_info *info);
int						init_resources(t_args *args);

#endif
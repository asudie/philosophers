/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmolnya <asmolnya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:14:15 by asmolnya          #+#    #+#             */
/*   Updated: 2024/12/13 21:31:31 by asmolnya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_args	args;

	if (argc < 5 || argc > 6 || check_args(argc, argv))
	{
		printf("Usage:\n"
			"\t%s number_of_philosophers time_to_die time_to_eat time_to_sleep "
			"[number_of_times_each_philosopher_must_eat]\n",
			argv[0]);
		return (1);
	}
	args.philos_num = ft_atoi(argv[1]);
	args.time2die = ft_atoi(argv[2]);
	args.time2eat = ft_atoi(argv[3]);
	args.time2sleep = ft_atoi(argv[4]);
	if (argc == 5)
		args.times2eat = -42;
	else
		args.times2eat = ft_atoi(argv[5]);
	if (check_values(&args))
		return (1);
	philos(&args);
	return (0);
}

// t_args args = {5, 800, 200, 200}; // No philosopher should die.
// t_args args = {4, 410, 200, 200}; // No philosopher should die.
// t_args args = {4, 310, 200, 100, -42}; // One philosopher should die.
// t_args args = {5, 800, 200, 200, 7}; // No philosopher should die.
// t_args args = {1, 800, 200, 200, -42}; // No eating, just die.
//./philo 201 2 3 4 5

// DATA RACE ./philo 1 2 3 4 4
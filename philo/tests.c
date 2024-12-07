#include "philo.h"

int main(int argc, char **argv)
// int main()
{
    if(argc < 5 || argc > 6 || check_args(argc, argv))
    {
        printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
        return 1;
    }
    t_args args;
        
    args.philos_num = ft_atoi(argv[1]);
    args.time2die = ft_atoi(argv[2]);
    args.time2eat = ft_atoi(argv[3]);
    args.time2sleep = ft_atoi(argv[4]);
    if(argc == 5)
        args.times2eat = -42;
    else
        args.times2eat = ft_atoi(argv[4]);

    if(check_values(&args))
            return 1;

    // FINISH INPUT VALIDATION
    
    // t_meal_info info;
    // info.args->philos_num = 6;
    // info.args->time2die = 5000;
    // info.args->time2eat = 1000;
    // info.args->time2sleep = 1000;
    // t_args args = {3, 3000, 1000, 1000};
    // t_args args = {5, 800, 200, 200}; // No philosopher should die.
    // t_args args = {4, 410, 200, 200}; // No philosopher should die. 
    // t_args args = {4, 310, 200, 100, -42}; // One philosopher should die. 
    // t_args args = {5, 800, 200, 200, 7}; // No philosopher should die.
    // t_args args = {1, 800, 200, 200, -42}; // No eating, just die.
    // t_args args = {4, 410, 200, 200, -42}; // No philosopher should die.
    // t_args args = {4, 310, 200, 100, -42}; // One philosopher should die.
    
    philos(&args);
    return 0;
}
#include "philo.h"

int main()
{
    // t_meal_info info;
    // info.args->philos_num = 6;
    // info.args->time2die = 5000;
    // info.args->time2eat = 1000;
    // info.args->time2sleep = 1000;
    // t_args args = {3, 3000, 1000, 1000};
    // t_args args = {5, 800, 200, 200}; // No philosopher should die.
    t_args args = {4, 410, 200, 200}; // No philosopher should die. 0 DIED!!!!!!!!!!!!!!!!!!!
    philos(&args);
    return 0;
}
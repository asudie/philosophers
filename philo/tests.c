#include "philo.h"

int main()
{
    t_meal_info info;
    info.args->philos_num = 6;
    info.args->time2die = 5000;
    info.args->time2eat = 1000;
    info.args->time2sleep = 1000;
    // {6, 5000, 1000, 1000};
    // allocate memory for t_args <----------------------------------
    philos(info);
    return 0;
}
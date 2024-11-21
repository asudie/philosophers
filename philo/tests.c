#include "philo.h"

int main()
{
    t_args my_args = {6, 5000, 1000, 1000};
    // allocate memory for t_args <----------------------------------
    philos(my_args);
    return 0;
}
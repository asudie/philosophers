#include "philo.h"

void *philosopher(void *arg)
{
    int id = (int *)(*arg)->id; // WHAT HERE
    int left_fork = id;
    int right_fork = (id + 1) % args.
}

int create_philos_and_forks(t_args my_args, pthread_mutex_t *forks, pthread_t *philos)
{
    // pthread_t philos[philos_num];
    int ids[my_args.philos_num];

    for (int i = 0; i < my_args.philos_num; i++) {
        pthread_mutex_init(&forks[i], NULL);
        ids[i] = i;
    }

    // PASS A STUCT TO void *philosopher(void *arg)

    for(int i = 0; i < my_args.philos_num; i++)
    {
        my_args.id = i;
        if(pthread_create(&philos[i], NULL, philosopher, &my_args) != 0)
        {
            perror("Failed to create thread");
            return 1;
        }
    }

    for(int i = 0; i < my_args.philos_num; i++)
    {
        pthread_join(philos[i], NULL);
    }
    return 0;
}

int philos(t_args  my_args)
{
    // t_args  my_args;
    pthread_mutex_t forks[my_args.philos_num];
    pthread_t philos[my_args.philos_num];
    
    // valid_input
    // my_args = make_struct;
    create_philos_and_forks(my_args, forks, philos);
    

}






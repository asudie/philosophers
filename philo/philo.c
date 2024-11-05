#include "philo.h"

void *philosopher()
{
    // CONTINUE HERE
}

int create_philos_and_forks(int philos_num, pthread_mutex_t *forks, pthread_t philos)
{
    // pthread_t philos[philos_num];
    int ids[philos_num];

    for(int i = 0; i < philos_num; i++)
    {
        pthread_mutex_init(&forks[i], NULL);
        ids[i] = i;
        if(pthread_create(&philos[i], NULL, philosopher, &ids[i]) != 0)
        {
            // CONTINUE HERE
        }
    }


}

int philos(t_args  my_args)
{
    // t_args  my_args;
    pthread_mutex_t forks[my_args.philos_num];
    pthread_t philos[my_args.philos_num];
    
    // valid_input
    // my_args = make_struct;
    create_philos_and_forks(my_args.philos_num, forks, philos);
    

}






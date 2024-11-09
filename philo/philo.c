#include "philo.h"

long get_time_ms(t_args *args)
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    long seconds = current_time.tv_sec - args->start_time.tv_sec;
    long microsec = current_time.tv_usec - args->start_time.tv_usec;
    retrun (seconds * 1000) + (microsec / 1000);
}

void *philosopher(void *arg)
{
    t_args *args = (t_args *)arg;
    long time;
    int id = args->id;
    int left_fork = id;
    int right_fork = (id + 1) % args->philos_num; // what if id > num_phil
    if(right_fork > args->philos_num)
        right_fork = 0;

    while(1)
    {
        time = get_time_ms(args);
        printf("%l %d is thinking\n", time, id);
        usleep(args->time2sleep);

        if(args->id % 2 == 0)
        {
            pthread_mutex_lock(&args->forks[left_fork]);
            pthread_mutex_lock(&args->forks[right_fork]);
        }


    }
}

int create_philos_and_forks(t_args my_args)
{
    // pthread_t philos[philos_num];
    int ids[my_args.philos_num];

    for (int i = 0; i < my_args.philos_num; i++) {
        pthread_mutex_init(&my_args.forks[i], NULL);
        ids[i] = i;
    }

    for(int i = 0; i < my_args.philos_num; i++)
    {
        my_args.id = i;
        if(pthread_create(&my_args.philos[i], NULL, philosopher, &my_args) != 0)
        {
            perror("Failed to create thread");
            return 1;
        }
    }

    for(int i = 0; i < my_args.philos_num; i++)
    {
        pthread_join(my_args.philos[i], NULL);
    }
    return 0;
}

int philos(t_args  my_args)
{
    // t_args  my_args;
    gettimeofday(&my_args.start_time, NULL);
    pthread_mutex_t forks[my_args.philos_num];
    pthread_t philos[my_args.philos_num];
    my_args.forks = forks;
    my_args.philos = philos;

    
    // valid_input
    // my_args = make_struct;
    create_philos_and_forks(my_args);
    

}






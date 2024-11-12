#include "philo.h"

long get_time_ms(t_args *args)
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    long seconds = current_time.tv_sec - args->start_time.tv_sec;
    long microsec = current_time.tv_usec - args->start_time.tv_usec;
    return (seconds * 1000) + (microsec / 1000);
}

void *philosopher(void *arg)
{
    t_args *args = (t_args *)arg;
    // long time;
    int id = args->id;
    int left_fork = id;
    int right_fork = (id + 1) % args->philos_num;
    if(right_fork > args->philos_num)
        right_fork = 0;

    while(1)
    {
        if(get_time_ms(args) >= args->time2die)
        {
            printf("%ld %d died\n", get_time_ms(args), id);
            return NULL; // will it finish like this???
        }
        if(args->id % 2 == 0)
        {
            pthread_mutex_lock(&args->forks[left_fork]);
            pthread_mutex_lock(&args->forks[right_fork]);
        } else
        {
            pthread_mutex_lock(&args->forks[right_fork]);
            pthread_mutex_lock(&args->forks[left_fork]);
        }
        // check time for dying
        if(get_time_ms(args) >= args->time2die)
        {
            args->philos[args->id] = 0;// check if others dead
            printf("%ld %d died\n", get_time_ms(args), id);
            return NULL; // will it finish like this???
        }
        printf("%ld %d is eating\n", get_time_ms(args), id);
        usleep(100 * args->time2eat);
        pthread_mutex_unlock(&args->forks[right_fork]);
        pthread_mutex_unlock(&args->forks[left_fork]);
        printf("%ld %d is sleeping\n", get_time_ms(args), id);
        usleep(100 * args->time2sleep);
        printf("%ld %d is thinking\n", get_time_ms(args), id);
        usleep(100 * 100);

    }
}

int create_philos_and_forks(t_args my_args)
{
    // pthread_t philos[philos_num];
    // int ids[my_args.philos_num];

    for (int i = 0; i < my_args.philos_num; i++) {
        pthread_mutex_init(&my_args.forks[i], NULL);
        // ids[i] = i + 1;
    }

    for(int i = 0; i < my_args.philos_num; i++)
    {
        my_args.id = i + 1;
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
    return 0;
}

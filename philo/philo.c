#include "philo.h"

long get_time_ms(t_args *args) {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    long seconds = current_time.tv_sec - args->start_time.tv_sec;
    long microsec = current_time.tv_usec - args->start_time.tv_usec;
    return (seconds * 1000) + (microsec / 1000);
}

int check_dead(t_args *args)
{
    if(*args->philosopher_died)
        return 1;
    long current_time = get_time_ms(args);
        if(current_time - args->last_meal_time >= args->time2die)
        {
            printf("%ld %d died\n", get_time_ms(args), args->id);
            *args->philosopher_died = 1;
            return 1; // do so it will finish after first death 
        }
        return 0;
}
void *philosopher(void *arg) {
    t_args *args = (t_args *)arg;
    int id = args->id;
    int left_fork = id;
    int right_fork = (id + 1) % args->philos_num;

    printf("%ld %d is here\n", get_time_ms(args), id);

    while (1) {
        if(check_dead(args))
            return NULL;
        if (get_time_ms(args) >= args->time2die) {
            printf("%ld %d died\n", get_time_ms(args), id);
            *args->philosopher_died = 1;
            return NULL;
        }
        
        if (id % 2 == 0) {
            pthread_mutex_lock(&args->forks[left_fork]);
            pthread_mutex_lock(&args->forks[right_fork]);
        } else {
            pthread_mutex_lock(&args->forks[right_fork]);
            pthread_mutex_lock(&args->forks[left_fork]);
        }

        if(check_dead(args))
            return NULL;
        
        printf("%ld %d is eating\n", get_time_ms(args), id);
        args->last_meal_time = get_time_ms(args);
        usleep(1000 * args->time2eat);
        pthread_mutex_unlock(&args->forks[right_fork]);
        pthread_mutex_unlock(&args->forks[left_fork]);
        if(check_dead(args))
            return NULL;
        printf("%ld %d is sleeping\n", get_time_ms(args), id);
        usleep(1000 * args->time2sleep);
        if(check_dead(args))
            return NULL;
        printf("%ld %d is thinking\n", get_time_ms(args), id);
        usleep(1000 * 100);
    }
}

t_args *args_copy(t_args args)
{
    t_args *temp_args = malloc(sizeof(t_args));
    if (!temp_args) {
            printf("Failed to allocate memory\n");
            return NULL;
        }
    temp_args->forks = args.forks;
    temp_args->id = args.id;
    temp_args->last_meal_time = args.last_meal_time;
    temp_args->philos = args.philos;
    temp_args->philos_num = args.philos_num;
    temp_args->philosopher_died = args.philosopher_died;
    temp_args->start_time = args.start_time;
    temp_args->time2die = args.time2die;
    temp_args->time2eat = args.time2eat;
    temp_args->time2sleep = args.time2sleep;

    return temp_args;
}

int create_philos_and_forks(t_args my_args) {
    pthread_mutex_t forks[my_args.philos_num];
    pthread_t philos[my_args.philos_num];
    pthread_t monitor_thread;

    my_args.forks = forks;
    my_args.philos = philos;
    int flag = 0;
    my_args.philosopher_died = &flag;
    for (int i = 0; i < my_args.philos_num; i++) {
        pthread_mutex_init(&my_args.forks[i], NULL);
        pthread_mutex_init(&my_args.not_shared[i].meal_time_mutex, NULL);
    }

    for (int i = 0; i < my_args.philos_num; i++) {
        t_args *temp_args;
        temp_args = args_copy(my_args); // continue changing for not_shared
        temp_args->id = i;  // What to do with id, should I create temp or should I send my args? should noy_shared be a massive?

        if (pthread_create(&my_args.philos[i], NULL, philosopher, temp_args) != 0) {
            printf("Failed to create philosopher\n");
            free(temp_args);
            return 1;
        }
    }
    if (pthread_create(&monitor_thread, NULL, monitor, &my_args) != 0) {
            printf("Failed to create philosopher\n");
            return 1;
    }


    for (int i = 0; i < my_args.philos_num; i++) {
        pthread_join(my_args.philos[i], NULL);
    }

    return 0;
}

int philos(t_args my_args) {
    gettimeofday(&my_args.start_time, NULL);
    return create_philos_and_forks(my_args);
}

void *monitor(void *arg)
{
    t_args *args = (t_args *)arg;

    while(1)
    {
        for(int i = 0; i < args->philos_num; i++)
        {
            long current_time = get_time_ms(args);
            pthread_mutex_lock(&args->meal_time_mutex[i]);
            if(current_time - args[i].last_meal_time >= args->time2die)
            {
                printf("%ld %d died\n", get_time_ms(args), args->id);
                *args->philosopher_died = 1;
                pthread_mutex_unlock(&args->meal_time_mutex[i]);
                return NULL;
            }
            pthread_mutex_unlock(&args->meal_time_mutex[i]);
        }
        usleep(1000);
    }
    return NULL;
}

// DO MONITORING PROCESS TO CHECK DEATHS <---------------------------------

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
    long current_time = get_time_ms(args);
        if(current_time - args->last_meal_time >= args->time2die)
        {
            printf("%ld %d died\n", get_time_ms(args), args->id);
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

        printf("%ld %d is sleeping\n", get_time_ms(args), id);
        usleep(1000 * args->time2sleep);
        printf("%ld %d is thinking\n", get_time_ms(args), id);
        usleep(1000 * 100);
    }
}

int create_philos_and_forks(t_args my_args) {
    pthread_mutex_t forks[my_args.philos_num];
    pthread_t philos[my_args.philos_num];

    my_args.forks = forks;
    my_args.philos = philos;
    for (int i = 0; i < my_args.philos_num; i++) {
        pthread_mutex_init(&my_args.forks[i], NULL);
    }

    for (int i = 0; i < my_args.philos_num; i++) {
        t_args *temp_args = malloc(sizeof(t_args));
        if (!temp_args) {
            printf("Failed to allocate memory\n");
            return 1;
        }
        *temp_args = my_args;
        temp_args->id = i + 1;  // Assign a unique id for each philosopher

        if (pthread_create(&my_args.philos[i], NULL, philosopher, temp_args) != 0) {
            printf("Failed to create thread\n");
            free(temp_args);
            return 1;
        }
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

// 0 1 is here
// 0 1 is eating
// 0 2 is here
// 0 3 is here
// 100 1 is sleeping
// 100 3 is eating  <- looks suspicious
// 100 2 is eating <- looks suspicious
// 200 1 is thinking
// 200 3 is sleeping
// 200 2 is sleeping
// 300 1 died
// 300 2 is thinking
// 300 3 is thinking
// 400 3 died
// 400 2 died
#include "philo.h"

long get_time_ms(t_args *args) {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    long seconds = current_time.tv_sec - args->start_time.tv_sec;
    long microsec = current_time.tv_usec - args->start_time.tv_usec;
    return (seconds * 1000) + (microsec / 1000);
}

void *philosopher(void *arg) {
    t_args *args = (t_args *)arg;
    int id = args->id;
    int left_fork = id;
    int right_fork = (id + 1) % args->philos_num;

    printf("%ld %d is here\n", get_time_ms(args), id);

    while (1) {
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

        if (get_time_ms(args) >= args->time2die) {
            printf("%ld %d died\n", get_time_ms(args), id);
            return NULL;
        }

        printf("%ld %d is eating\n", get_time_ms(args), id);
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
#include "philo.h"

long get_time_ms(t_args *args) {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    long seconds = current_time.tv_sec - args->start_time.tv_sec;
    long microsec = current_time.tv_usec - args->start_time.tv_usec;
    return (seconds * 1000) + (microsec / 1000);
}

// int check_dead(t_meal_info *info)
// {
//     if(*args->philosopher_died)
//         return 1;
//     long current_time = get_time_ms(args);
//         if(current_time - args->last_meal_time >= args->time2die)
//         {
//             printf("%ld %d died\n", get_time_ms(args), args->id);
//             *args->philosopher_died = 1;
//             return 1; // do so it will finish after first death 
//         }
//         return 0;
// }

void *philosopher(void *arg) {
    t_meal_info *info = (t_meal_info *)arg;
    int id = info->id;
    int left_fork = id;
    int right_fork = (id + 1) % info->args->philos_num;

    printf("%ld %d is here\n", get_time_ms(info->args), id);

    while (1) {
        // if(check_dead(args))
        //     return NULL;
        // if (get_time_ms(args) >= args->time2die) {
        //     printf("%ld %d died\n", get_time_ms(args), id);
        //     *args->philosopher_died = 1;
        //     return NULL;
        // }
        
        if (id % 2 == 0) {
            pthread_mutex_lock(&info->args->forks[left_fork]);
            pthread_mutex_lock(&info->args->forks[right_fork]);
        } else {
            pthread_mutex_lock(&info->args->forks[right_fork]);
            pthread_mutex_lock(&info->args->forks[left_fork]);
        }

        // if(check_dead(args))
        //     return NULL;
        
        printf("%ld %d is eating\n", get_time_ms(info->args), id);
        info->last_meal_time = get_time_ms(info->args);
        usleep(1000 * info->args->time2eat);
        pthread_mutex_unlock(&info->args->forks[right_fork]);
        pthread_mutex_unlock(&info->args->forks[left_fork]);
        // if(check_dead(args))
        //     return NULL;
        printf("%ld %d is sleeping\n", get_time_ms(info->args), id);
        usleep(1000 * info->args->time2sleep);
        // if(check_dead(args))
        //     return NULL;
        printf("%ld %d is thinking\n", get_time_ms(info->args), id);
        usleep(1000 * 100);
    }
}

// t_args *args_copy(t_meal_info  *info)
// {
//     t_meal_info *temp_info = malloc(sizeof(t_args));
//     if (!temp_info) {
//             printf("Failed to allocate memory\n");
//             return NULL;
//         }
//     // temp_info->args = malloc(sizeof(t_args));
//     temp_info->args->forks = info->args->forks;
//     temp_info->id = info->id;
//     temp_info->args = info->args;
//     temp_info->meal_time_mutex = info->meal_time_mutex;
//     temp_info->last_meal_time = info->last_meal_time;
//     // temp_info->args->philos = info->args->philos;
//     // temp_info->args->philos_num = info->args->philos_num;
//     // temp_info->args->philosopher_died = info->args->philosopher_died;
//     // temp_info->args->start_time = info->args->start_time;
//     // temp_info->args->time2die = info->args->time2die;
//     // temp_info->args->time2eat = info->args->time2eat;
//     // temp_info->args->time2sleep = info->args->time2sleep;

//     return temp_info;
// }

int create_philos_and_forks(t_args  *args) {
    pthread_mutex_t forks[args->philos_num];
    pthread_t philos[args->philos_num];
    pthread_t monitor_thread;

    args->forks = forks;
    args->philos = philos;
    int flag = 0;
    args->philosopher_died = &flag;
    args->info = malloc(sizeof(t_meal_info) * args->philos_num);
    for (int i = 0; i < args->philos_num; i++) {
        pthread_mutex_init(&args->forks[i], NULL);
        pthread_mutex_init(&args->info[i].meal_time_mutex, NULL);
        args->info[i].args = args;
        args->info[i].id = i;
        args->info[i].last_meal_time = 0;
        if (pthread_create(&args->philos[i], NULL, philosopher, &args->info[i]) != 0) {
            printf("Failed to create philosopher\n");
            return 1;
        }
    }

    // for (int i = 0; i < args->philos_num; i++) {
    //     // t_args *temp_args;
    //     // temp_args = args_copy(args); // continue changing for not_shared
    //     // temp_args->id = i;  // What to do with id, should I create temp or should I send my args? should noy_shared be a massive?

    //     if (pthread_create(&info->args->philos[i], NULL, philosopher, temp_info) != 0) {
    //         printf("Failed to create philosopher\n");
    //         free(temp_info);
    //         return 1;
    //     }
    //     // free(temp_info);
    // }
    if (pthread_create(&monitor_thread, NULL, monitor, &args->info) != 0) {
            printf("Failed to create philosopher\n");
            return 1;
    }
    for (int i = 0; i < args->philos_num; i++) {
        pthread_join(args->philos[i], NULL);
    }

    return 0;
}

int philos(t_args  *args) {
    gettimeofday(&args->start_time, NULL);
    return create_philos_and_forks(args);
}

void *monitor(void *arg)
{
    t_meal_info *info = (t_meal_info *)arg;

    while(1)
    {
        for(int i = 0; i < info->args->philos_num; i++)
        {
            long current_time = get_time_ms(info->args);
            pthread_mutex_lock(&info[i].meal_time_mutex);
            if(current_time - info[i].last_meal_time >= info->args->time2die) // how monitor should know about 
            {
                printf("%ld %d died\n", get_time_ms(info->args), info->id);
                *info->args->philosopher_died = 1;
                pthread_mutex_unlock(&info[i].meal_time_mutex);
                return NULL;
            }
            pthread_mutex_unlock(&info[i].meal_time_mutex);
        }
        usleep(1000);
    }
    return NULL;
}

// DO MONITORING PROCESS TO CHECK DEATHS <---------------------------------

#include "philo.h"

long get_time_ms(t_args *args) {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    long seconds = current_time.tv_sec - args->start_time.tv_sec;
    long microsec = current_time.tv_usec - args->start_time.tv_usec;
    return (seconds * 1000) + (microsec / 1000);
}

void *philosopher(void *arg) {
    t_meal_info *info = (t_meal_info *)arg;
    int id = info->id;
    int left_fork = id;
    int right_fork = (id + 1) % info->args->philos_num;
    int meals_count = 0;

    printf("%ld %d is here\n", get_time_ms(info->args), id);

    while (1) {
        if (*info->args->philosopher_died) {
            return NULL;
        }
        
        if (id % 2 == 0) {
            pthread_mutex_lock(&info->args->forks[left_fork]);
            pthread_mutex_lock(&info->args->forks[right_fork]);
        } else {
            pthread_mutex_lock(&info->args->forks[right_fork]);
            pthread_mutex_lock(&info->args->forks[left_fork]);
        }
        if (*info->args->philosopher_died) {
            return NULL; 
        }
        pthread_mutex_lock(&info->full_mutex);
        if(info->args->times2eat > 0) // what if 0
            info->philosopher_full++;
        pthread_mutex_unlock(&info->full_mutex);
        printf("%ld %d is eating\n", get_time_ms(info->args), id);
        info->last_meal_time = get_time_ms(info->args);
        usleep(1000 * info->args->time2eat);
        pthread_mutex_unlock(&info->args->forks[right_fork]);
        pthread_mutex_unlock(&info->args->forks[left_fork]);
        if (*info->args->philosopher_died) {
            return NULL;
        }
        printf("%ld %d is sleeping\n", get_time_ms(info->args), id);
        usleep(1000 * info->args->time2sleep);
        if (*info->args->philosopher_died) {
            return NULL;
        }
        printf("%ld %d is thinking\n", get_time_ms(info->args), id);
        usleep(1000);
    }
}

int create_philos_and_forks(t_args  *args) {
    pthread_t monitor_thread;

    args->forks = malloc(sizeof(pthread_mutex_t) * args->philos_num);
    args->philos = malloc(sizeof(pthread_t) * args->philos_num);
    args->info = malloc(sizeof(t_meal_info) * args->philos_num);
    if (!args->forks || !args->philos || !args->info) {
        printf("Failed to allocate memory for forks, info or philos\n");
        return 1;
    }
    int death = 0;
    // int full = 0;
    args->philosopher_died = &death;
    // args->info->philosopher_full = &full;
    for (int i = 0; i < args->philos_num; i++) {
        pthread_mutex_init(&args->forks[i], NULL);
        pthread_mutex_init(&args->info[i].meal_time_mutex, NULL);
        pthread_mutex_init(&args->info[i].full_mutex, NULL);
        args->info[i].args = args;
        args->info[i].id = i;
        args->info[i].last_meal_time = get_time_ms(args);
        if (pthread_create(&args->philos[i], NULL, philosopher, &args->info[i]) != 0) {
            printf("Failed to create philosopher\n");
            return 1;
        }
    }
    if (pthread_create(&monitor_thread, NULL, monitor, args->info) != 0) {
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

int check_full(t_meal_info *info)
{

    for (int i = 0; i < info->args->philos_num; i++)
    {
        pthread_mutex_lock(&info[i].full_mutex); // add mutex to eating
        if(info[i].philosopher_full < info->args->times2eat)
        {
            pthread_mutex_unlock(&info[i].full_mutex);
            return 0;
        }
        pthread_mutex_unlock(&info[i].full_mutex); 
    }
    printf("FULL!!!\n");
    return 1;
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
                // printf("MONITORING\n");
                printf("%ld %d died\n", get_time_ms(info->args), info->id);
                *info->args->philosopher_died = 1;
                pthread_mutex_unlock(&info[i].meal_time_mutex);
                return NULL;
            }
            pthread_mutex_unlock(&info[i].meal_time_mutex);
            
            if(check_full(info))
                return NULL;  
        }
        usleep(1000);
    }
    return NULL;
}

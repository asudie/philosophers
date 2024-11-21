#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>

typedef struct s_args 
{
    int philos_num;
    int time2die;
    int time2eat; 
    int time2sleep;
    // int times2eat;
    pthread_mutex_t *forks;
    pthread_t *philos;
    t_meal_info *not_shared;
    int *philosopher_died;
    pthread_mutex_t death_mutex;
    struct timeval start_time;
}   t_args;

typedef struct s_meal_info
{
    long last_meal_time;
    pthread_mutex_t *meal_time_mutex;
    int id;
} t_meal_info;

int philos(t_args  my_args);
int create_philos_and_forks(t_args my_args);
void *philosopher(void *arg);
long get_time_ms(t_args *args);
void *monitor(void *arg);
// typedef struct s_func_args 
// {
//     int philos_num;
// }   t_func_args;


#endif
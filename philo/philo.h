#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>

typedef struct s_args t_args;

typedef struct s_meal_info
{
    long last_meal_time;
    pthread_mutex_t meal_time_mutex;
    int id;
    int meal_count;
    pthread_mutex_t full_mutex; // put it to args, change this flag in philos and catch it in monitor
    t_args *args;
} t_meal_info;

typedef struct s_args 
{
    int philos_num;
    int time2die;
    int time2eat; 
    int time2sleep;
    int times2eat;
    pthread_mutex_t *forks;
    pthread_t *philos;
    t_meal_info *info;
    int *philosopher_died;
    int *full_stop;
    pthread_mutex_t death_mutex;
    struct timeval start_time;
}   t_args;



int philos(t_args  *args);
int create_philos_and_forks(t_args  *args);
void *philosopher(void *arg);
long get_time_ms(t_args  *args);
void *monitor(void *arg);
int check_full(t_meal_info *info);
void *handle_one(t_meal_info *info);



#endif
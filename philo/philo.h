#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

typedef struct s_args 
{
    int philos_num;
    int time2die;
    int time2eat; 
    int time2sleep;
    // int times2eat;
    int id;
}   t_args;

// typedef struct s_func_args 
// {
//     int philos_num;
// }   t_func_args;


#endif
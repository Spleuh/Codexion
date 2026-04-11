#include "codexion.h"

void    *scheduling(void *arg)
{
    t_data    *data;
    t_dongle    *dongles;
    int     i;
    int     stop;
    long    lst_cmp_0;
    long    lst_cmp_1;
    

    data = (t_data *)arg;
    dongles = data->dongles;
    pthread_mutex_lock(&data->mutex_start);
    while (!data->start_sim)
        pthread_cond_wait(&data->cond_start, &data->mutex_start);
    pthread_mutex_unlock(&data->mutex_start);

    pthread_mutex_lock(&data->mutex_stop);
    stop = data->stop_sim;
    pthread_mutex_unlock(&data->mutex_stop);
    while (!stop)
    {
        i = 0;
        while (i < dongles[0].n_dongles)
        {
            pthread_mutex_lock(&dongles[i].mutex_lst_cmp);
            lst_cmp_0 = dongles[i].lst_cmp_0;
            lst_cmp_1 = dongles[i].lst_cmp_1;
            if (lst_cmp_0 < lst_cmp_1)
                dongles[i].id_priority = dongles[i].id;
            else if (lst_cmp_0 >= lst_cmp_1)
                dongles[i].id_priority = (dongles[i].id - 1 + dongles[i].n_dongles) % dongles[i].n_dongles;
            pthread_mutex_unlock(&dongles[i].mutex_lst_cmp);
            i++;
        }
        pthread_mutex_lock(&data->mutex_stop);
        stop = data->stop_sim;
        pthread_mutex_unlock(&data->mutex_stop);
    }
    return (NULL);
}

int init_scheduler(t_data *data)
{
    pthread_create(&data->thread_planner, NULL, scheduling, data);
    return (0);
}
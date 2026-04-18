#include "codexion.h"

void    destroy_mutex_cond_data(t_data *data)
{
    pthread_mutex_destroy(&data->mutex_print);
    pthread_mutex_destroy(&data->mutex_state_sim);
    pthread_mutex_destroy(&data->mutex_state_dongles);
    pthread_cond_destroy(&data->cond_start);
    pthread_cond_destroy(&data->cond_state_dongles);
    return ;
}

void    cleanup_dongles_coders(t_data *data)
{
    if (data->dongles)
        cleanup_dongles(data); 
    if (data->coders)
        cleanup_coders(data);
}

void    cleanup_data(t_data *data)
{
    destroy_mutex_cond_data(data);
    pthread_cond_destroy(&data->cond_start);
    cleanup_dongles_coders(data);
    free(data);
}
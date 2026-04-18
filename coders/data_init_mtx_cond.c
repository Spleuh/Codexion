#include "codexion.h"

int     init_cond_data(t_data *data)
{    
    if (pthread_cond_init(&data->cond_start, NULL) != 0)
        return (1);
    if (pthread_cond_init(&data->cond_state_dongles) != 0)
    {
        pthread_cond_destroy(&data->cond_start);
        return (1);
    }
    return (0);
}

int     init_mutex_data(t_data *data)
{
    if (pthread_mutex_init(&data->mutex_print, NULL) != 0)
        return (1);
    if (pthread_mutex_init(&data->mutex_state_sim, NULL) != 0)
    {
        pthread_mutex_destroy(&data->mutex_print);
        return (1);
    }
    if (pthread_mutex_init(&data->mutex_state_dongles) != 0)
    {
        pthread_mutex_destroy(&data->mutex_print);
        pthread_mutex_destroy(&data->mutex_state_sim);
        return (1);
    }
    return (0);
}

int     init_mutex_cond_data(t_data *data)
{
    if (init_cond_data(data) != 0)
        return (1);
    if (init_mutex_data(data) != 0)
    {
        pthread_cond_destroy(&data->cond_start);
        pthread_cond_destroy(&data->cond_state_dongles);
        return (1);
    }
    return (0);
}
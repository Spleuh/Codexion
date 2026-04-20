#include "codexion.h"

int     get_stop_sim(t_data *data)
{
    int result;

    pthread_mutex_lock(&data->mutex_state_sim);
    result = data->stop_sim;
    pthread_mutex_unlock(&data->mutex_state_sim);
    return (result);
}

void    set_stop_sim(t_data *data, int i)
{
    pthread_mutex_lock(&data->mutex_state_sim);
    data->stop_sim = i;
    pthread_mutex_unlock(&data->mutex_state_sim);
}

void    incr_count_ready(t_data *data)
{
    pthread_mutex_lock(&data->mutex_state_sim);
    data->count_ready++;
    pthread_mutex_unlock(&data->mutex_state_sim);
}

void    decr_count_ready(t_data *data)
{
    pthread_mutex_lock(&data->mutex_state_sim);
    data->count_ready--;
    pthread_mutex_unlock(&data->mutex_state_sim);
}

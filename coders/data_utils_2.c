#include "codexion.h"

int     get_stop_sim(t_data *data)
{
    int result;

    pthread_mutex_lock(&data->mutex_env->mutex_state_sim);
    result = data->stop_sim;
    pthread_mutex_unlock(&data->mutex_env->mutex_state_sim);
    return (result);
}

void    set_stop_sim(t_data *data, int i)
{
    pthread_mutex_lock(&data->mutex_env->mutex_state_sim);
    data->stop_sim = i;
    pthread_mutex_unlock(&data->mutex_env->mutex_state_sim);
}


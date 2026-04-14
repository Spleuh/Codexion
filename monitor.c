#include "codexion.h"

int         get_stop_sim(t_data *data)
{
    int result;

    pthread_mutex_lock(&data->mutex_data);
    result = data->stop_sim;
    pthread_mutex_unlock(&data->mutex_data);
    return (result);
}

t_monitor   *init_monitor(t_data *data)
{
    t_monitor *monitor;

    monitor = malloc(sizeof(t_monitor));
    if (!monitor)
        return (NULL);
    monitor->coders = data->coders;
    monitor->data= data;
    return (monitor);
}
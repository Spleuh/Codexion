#include "codexion.h"

void    *routine_monitor(void *arg)
{
    t_monitor *monitor;
    int     i;
    int     all_done;
    int     n_coders;
    int     n_compile;

    monitor = (t_monitor *)arg;
    n_coders = monitor->data->args->n_coders;
    n_compile = monitor->data->args->n_compiles;
    pthread_mutex_lock(&monitor->data->mutex_env->mutex_state_sim);
    while (!monitor->data->start_sim)
        pthread_cond_wait(&monitor->data->cond_start, &monitor->data->mutex_env->mutex_state_sim);
    pthread_mutex_unlock(&monitor->data->mutex_env->mutex_state_sim);
    if (get_cancel_sim(monitor->data))
        return (NULL);
    while (!get_stop_sim(monitor->data))
    {
        i = 0;
        all_done = 1;
        while (i < n_coders)
        {   
            if (get_compile_done(&monitor->coders[i]) < n_compile)
                all_done = 0;
            if (get)
            i++;
        }
        if (all_done == 1)
        {
            set_stop_sim(monitor->data, 1);
        }
    }
    return (NULL);
}
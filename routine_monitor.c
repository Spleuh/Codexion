#include "codexion.h"

void    print_stop_burned_out(t_monitor *monitor, int id)
{
    long    timestamp;

    timestamp = get_timestamp() - monitor->data->timestamp_start;
    pthread_mutex_lock(&monitor->data->mutex_env->mutex_print);
    pthread_mutex_lock(&monitor->data->mutex_env->mutex_state_sim);
    monitor->data->stop_sim = 1;
    printf("%ld %d burned out\n", timestamp, id);
    pthread_mutex_unlock(&monitor->data->mutex_env->mutex_print);
    pthread_mutex_unlock(&monitor->data->mutex_env->mutex_state_sim);
}

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
    while (get_stop_sim(monitor->data) == 0)
    {
        i = 0;
        all_done = 1;
        while (i < n_coders)
        {   
            if (get_compile_done(&monitor->coders[i]) < n_compile)
                all_done = 0;
            if (get_last_comp_start(&monitor->coders[i]) + monitor->data->args->t_burnout < get_timestamp() - monitor->data->timestamp_start)
                print_stop_burned_out(monitor, monitor->coders[i].id);
            i++;
        }
        if (all_done == 1 && get_stop_sim(monitor->data) == 0)
        {
            set_stop_sim(monitor->data, 1);
            pthread_cond_broadcast(&monitor->data->cond_entry);
        }
    }
    return (NULL);
}
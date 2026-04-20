#include "codexion.h"

void    send_broadcast_state_dongle(t_data *data)
{
    pthread_mutex_lock(&data->mutex_state_dongles);
    pthread_cond_broadcast(&data->cond_state_dongles);
    pthread_mutex_unlock(&data->mutex_state_dongles);
}

long    find_next_cooldown(t_data *data)
{
    int     i;
    long    result;
    
    i = 0;
    pthread_mutex_lock(&data->mutex_state_dongles);
    result = data->dongles[0].end_cooldown;
    while (i < data->n_coders - 1)
    {
        if (result > data->dongles[i].end_cooldown)
            result = data->dongles[i].end_cooldown;
        i++;
    }
    pthread_mutex_unlock(&data->mutex_state_dongles);
    return (result);
}

void    check_all(t_data *data)
{
    int     i;
    int     all_done;

    i = 0;
    all_done = 1;
    while (i < data->n_coders)
    {
        if (find_next_cooldown(data) < get_timestamp(data))
            send_broadcast_state_dongle(data);
        if (get_compile_done(&data->coders[i]) < data->n_compiles)
            all_done = 0;
        if (get_last_comp_start(&data->coders[i]) + data->t_burnout < get_timestamp(data))
        {
            print_stop_burned_out(data, data->coders[i].id);
            return ;
        }
        i++;
    }
    if (all_done == 1)
        set_stop_sim(data, 1);
}

void    *routine_monitor(void *arg)
{
    t_data  *data;

    data = (t_data *)arg;
    incr_count_ready(data);
    pthread_mutex_lock(&data->mutex_state_sim);
    while (data->start_sim == 0)
        pthread_cond_wait(&data->cond_start, &data->mutex_state_sim);
    pthread_mutex_unlock(&data->mutex_state_sim);
    if (get_cancel_sim(data))
        return (NULL);
    while (get_stop_sim(data) == 0)
        check_all(data);
    // decr_count_ready(data);
    return (NULL);
}
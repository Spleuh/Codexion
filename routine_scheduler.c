#include "codexion.h"

t_dongle    **get_dbl_ptr(t_dongle *dongles, int n)
{
    int i;
    t_dongle    **result;
    
    result = malloc(sizeof(t_dongle *) * n);
    if (!result)
        return (NULL);
    i = 0;
    while (i < n)
    {
        result[i] = &dongles[i];
        i++;
    }
    return (result);
}

void    *routine_scheduler(void *arg)
{
    int i;
    // int index;
    t_scheduler *scheduler;
    t_dongle    *test;
    t_dongle    **tmp;

    scheduler = (t_scheduler *)arg;
    // dongles = get_dbl_ptr(scheduler->dongles, scheduler->data->args->n_coders);
    // if (!dongles)
        // return (NULL);
    pthread_mutex_lock(&scheduler->data->mutex_env->mutex_state_sim);
    while (!scheduler->data->start_sim)
        pthread_cond_wait(&scheduler->data->cond_start, &scheduler->data->mutex_env->mutex_state_sim);
    pthread_mutex_unlock(&scheduler->data->mutex_env->mutex_state_sim);
    if (get_cancel_sim(scheduler->data))
        return (NULL);
    i = 0;
    while (!get_stop_sim(scheduler->data))
    {
        i = 0;
        while (i < scheduler->data->args->n_coders)
        {
            if (get_end_cooldown(&scheduler->dongles[i]) < get_timestamp() - scheduler->data->timestamp_start)
            {
                test = &scheduler->dongles[i];
                tmp = &test;
                set_available(tmp, 1);
            }
            i++;
        }
    }
    return (NULL);
}
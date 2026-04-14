#include "codexion.h"

int (*get_scheduler(char*))(int, t_dongle*, t_dongle*)
{
    int (*f)(int, t_dongle*, t_dongle*);

    if (strcmp(coder->data->scheduler, "fifo") == 0)
        f = &check_available;
    else if (strcmp(coder->data->scheduler, "edf") == 0)
        f = &check_id_priority;
    return (f);
}

int     lock_mutex_dongles(t_dongle *first, t_dongle *second)
{
    if (pthread_mutex_lock(&first->mutex_dongle) != 0)
        return (1);
    if (pthread_mutex_lock(&second->mutex_dongle) != 0)
    {
        pthread_mutex_unlock(&first->mutex_dongle);
        return (1);
    }
    return (0);
}
int     lock_mutex_state_dongles(t_dongle *first, t_dongle *second)
{
    if (pthread_mutex_lock(&first->mutex_state) != 0)
        return (1);
    if (pthread_mutex_lock(&second->mutex_state) != 0)
    {
        pthread_mutex_unlock(&first->mutex_state);
        return (1);
    }
    return (0);
}

void    take_dongles(t_coder *coder, t_dongle *first, t_dongle *second)
{
    long    timestamp;
    int (*f)(int, t_dongle*, t_dongle*);
    
    f = get_scheduler(coder->data->args->schedule);
    pthread_mutex_lock(coder->data->mutex_entry);

    while(1)
    {
        while (!f(coder->id, first, second))
            pthread_cond_wait(&coder->data->cond_entry, &coder->data->mutex_entry);
        if(!lock_mutex_dongles(first, second))
            break;
    }
    set_available(first, 0);
    set_available(second, 0);

    // pthread_mutex_lock(&coder->data->mutex_print);
    // timestamp = get_timestamp() - coder->data->timestamp_start;
    // printf("%ld %d has taken dongle %d\n",timestamp, coder->id, first->id);
    // printf("%ld %d has taken dongle %d\n",timestamp, coder->id, second->id);
    // pthread_mutex_unlock(&coder->data->mutex_print);
}
void    compile(t_coder *coder)
{

}

void    *routine_coder(void *arg)
{
    t_coder *coder = (t_coder *)arg;

    pthread_mutex_lock(&coder->data->mutex_start);
    while (!coder->data->start_sim)
        pthread_cond_wait(&coder->data->cond_start, &coder->data->mutex_start);
    pthread_mutex_unlock(&coder->data->mutex_start);

    if (get_cancel_sim(coder->data))
        return (NULL);

    while (!get_stop_sim(coder->data))
    {
        compile(coder);
        debug(coder);
        refactor(coder);

    }
    return (NULL);
}
#include "codexion.h"

void    *monitoring(void *arg)
{
    t_coder  *coders;
    int     i;
    int     all_done;

    coders = (t_coder *)arg;
    pthread_mutex_lock(&coders[0].data->mutex_start);
    while (!coders[0].data->start_sim)
        pthread_cond_wait(&coders[0].data->cond_start, &coders[0].data->mutex_start);
    pthread_mutex_unlock(&coders[0].data->mutex_start);
    while (!coders[0].data->stop_sim)
    {
        i = 0;
        all_done = 1;
        while (i < coders[0].data->n_coders)
        {
            if (coders[i].compiles_done < coders[0].data->n_compiles)
                all_done = 0;
            i++;
        }
        if (all_done == 1)
        {
            pthread_mutex_lock(&coders[0].data->mutex_stop);
            coders[0].data->stop_sim = 1;
            pthread_mutex_unlock(&coders[0].data->mutex_stop);
        }
    }
    return (NULL);
}


int init_monitor(t_coder *coder)
{
    pthread_create(&coder[0].data->monitor, NULL, monitoring, coder);
    return (0);
}
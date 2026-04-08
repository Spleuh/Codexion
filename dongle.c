#include "codexion.h"

int init_dongles(t_data *data)
{
    int i;

    i = 0;
    data->dongles = malloc(sizeof(t_dongle) * data->n_coders);
    if (!data->dongles)
        return (1);
    while (i < data->n_coders)
    {
        data->dongles[i]->id = i;
        data->dongles[i]->end_cooldown = 0;
        data->dongles[i]->available = 1;
        if (pthread_mutex_init(&data->dongles[i]->mutex, NULL) != 0)
            break ;
        if (pthread_cond_init(&data->dongles[i], NULL) != 0)
        {
            pthread_mutex_destroy(&data->dongles[i]);
            break ;
        }
        i++;
    }
    if (i < data->n_coders)
    {
        while(i > 0)
        {
            pthread_mutex_destroy(&data->dongles[i]);
            pthread_cond_destroy(&data->dongles[i]);
            i--;
        }
        return (1);
    }
    return (0);
}
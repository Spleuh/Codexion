#include "codexion.h"

void    init_args_dongles(t_dongle *dongles, int n, t_data *data)
{
    int i;

    i = 0;
    while (i < n)
    {
        dongles[i].id = i;
        dongles[i].available = 1;
        dongles[i].end_cooldown = -1;
        dongles[i].mutex_state_dongles = &data->mutex_state_dongles;
        dongles[i].cond_state_dongles = &data->cond_state_dongles;
        i++;
    }
}

int     init_queue_dongle(t_dongle *dongle)
{

    dongle->queue = malloc(sizeof(t_heap));
    if (!dongle->queue)
        return (1);
    dongle->queue->size = 0;
    dongle->queue->max_size = 2;
    dongle->queue->tree = malloc(sizeof(t_node) * 2);
    if (!dongle->queue->tree)
    {
        free(dongle->queue);
        return (1);
    }
    return (0);
}

int     init_queue_dongles(t_dongle *dongles, int n)
{
    int i;
    
    i = 0;
    while (i < n)
    {
        if (init_queue_dongle(&dongles[i]) != 0)
        {
            free_queue_dongles(i, dongles);
            return (1);
        }
        i++;
    }
    return (0);
}

int     init_mutex_dongles(t_dongle *dongles, int n)
{
    int i;

    i = 0;
    while (i < n)
    {
        if (pthread_mutex_init(&dongles[i].mutex_dongle, NULL) != 0)
        {
            destroy_mutex_dongles(i, dongles);
            return (1);
        }
        i++;
    }
    return (0);
}

int     init_dongles(t_data *data)
{
    data->dongles = malloc(sizeof(t_dongle) * data->n_coders);
    if (!data->dongles)
        return (1);
    init_args_dongles(data->dongles, data->n_coders, data);
    if (init_queue_dongles(data->dongles, data->n_coders) != 0)
    {
        free(data->dongles);
        return (1);
    }
    if (init_mutex_dongles(data->dongles, data->n_coders) != 0)
    {
        free_queue_dongles(data->n_coders, data->dongles);
        free(data->dongles);
        return (1);
    }
    return (0);
}
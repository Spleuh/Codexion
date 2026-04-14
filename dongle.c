#include "codexion.h"

void    set_available(t_dongle *dongle, int i)
{
    pthread_mutex_lock(&dongle->mutex_dongle);
    dongle->available = i;
    pthread_mutex_unlock(&dongle->mutex_dongle);
}

void    free_dongles(int i, t_dongle *dongles)
{
    destroy_mutex_dongles(i, dongles);
    free(dongles);
}

void    destroy_mutex_dongles(int i, t_dongle *dongles)
{
    i--;
    while (i >= 0)
    {
        pthread_mutex_destroy(&dongles->mutex_dongle);
        pthread_mutex_destroy(&dongles->mutex_state); 
        i--;
    }
}

int     init_mutex_dongles(t_dongle *dongles, int n)
{
    int i;

    i = 0;
    while (i < n)
    {
        if (pthread_mutex_init(&dongles[i].mutex_dongle, NULL) != 0)
            return (i++);
        if (pthread_mutex_init(&dongles[i].mutex_state, NULL) != 0)
        {
            pthread_mutex_destroy(&dongles[i].mutex_dongle);
            return (i++);
        }
        i++;
    }
    return (0);
}
t_dongle    *init_dongles(t_args *args)
{
    t_dongle *dongles;
    int       i;

    dongles = malloc(sizeof(t_dongle) * args->n_coders);
    if (!dongles)
        return (NULL);
    while (i < args->n_coders)
    {
        dongles[i].id = i;
        dongles[i].available = 1;
        dongles[i].id_priority = -1;
        dongles[i].end_cooldown = -1;
        i++;
    }
    return (dongles);
}
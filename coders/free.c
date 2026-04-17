#include "codexion.h"

void    destroy_cond_data(t_data *data)
{
    pthread_cond_destroy(&data->cond_entry);
    pthread_cond_destroy(&data->cond_start);
    return ;
}

void    destroy_mutex_dongles(int i, t_dongle *dongles)
{
    i--;
    while (i >= 0)
    {
        pthread_mutex_destroy(&dongles[i].mutex_dongle);
        i--;
    }
}

void    free_dongles(int i, t_dongle *dongles)
{
    destroy_mutex_dongles(i, dongles);
    free(dongles);
}

void    destroy_mutex_coders(t_coder *coders, int n)
{
    int i;

    i = 0;
    while (i < n)
    {
        print_debug("destroy mutex free coders");
        pthread_mutex_destroy(&coders[i].mutex_coder);
        i++;
    }
}

void    free_data(t_data *data)
{
    if (data->coders)
        free(data->coders);
    if (data->dongles)
        free(data->dongles)
    free(data);
}


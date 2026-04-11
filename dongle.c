#include "codexion.h"

void    free_dongles(t_dongle *dongles, int n_dongles)
{
    int i;

    i = 0;
    while (i < n_dongles)
    {
        pthread_mutex_destroy(&dongles[i].mutex);
        i++;
    }
    free(dongles);
    return ;
}

int init_dongles(t_data *data)
{
    int i;

    i = 0;
    data->dongles = malloc(sizeof(t_dongle) * data->n_coders);
    if (!data->dongles)
        return (1);
    while (i < data->n_coders)
    {
        data->dongles[i].id = i;
        data->dongles[i].end_cooldown = 0;
        data->dongles[i].available = 1;
        data->dongles[i].id_priority = -1;
        data->dongles[i].lst_cmp_0 = -1;
        data->dongles[i].lst_cmp_1 = -1;
        if (pthread_mutex_init(&data->dongles[i].mutex, NULL) != 0)
            break;
        if (pthread_mutex_init(&data->dongles[i].mutex_lst_cmp, NULL) != 0)
        {
            pthread_mutex_destroy(&data->dongles[i].mutex);
            break;
        }
        if (pthread_mutex_init(&data->dongles[i].mutex_available, NULL) != 0)
        {
            pthread_mutex_destroy(&data->dongles[i].mutex);
            pthread_mutex_destroy(&data->dongles[i].mutex_lst_cmp);
            break;
        }
        if (pthread_mutex_init(&data->dongles[i].mutex_id_priority, NULL) != 0)
        {
            pthread_mutex_destroy(&data->dongles[i].mutex);
            pthread_mutex_destroy(&data->dongles[i].mutex_lst_cmp);
            pthread_mutex_destroy(&data->dongles[i].mutex_available);
            break;
        }
        i++;
    }
    if (i < data->n_coders)
    {
        while(i > 0)
        {   
            i--;
            pthread_mutex_destroy(&data->dongles[i].mutex);
            pthread_mutex_destroy(&data->dongles[i].mutex_lst_cmp);
            pthread_mutex_destroy(&data->dongles[i].mutex_available);
            pthread_mutex_destroy(&data->dongles[i].mutex_id_priority);
        }
        free(data->dongles);
        return (1);
    }
    return (0);
}
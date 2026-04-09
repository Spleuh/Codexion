#include "codexion.h"

void    free_dongles(t_dongle *dongles, int n_dongles)
{
    int i;

    i = 0;
    while (i < n_dongles)
    {
        free_heap(dongles[i].heap);
        pthread_mutex_destroy(&dongles[i].mutex);
        pthread_cond_destroy(&dongles[i].cond);
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
        data->dongles[i].heap = init_heap();
        if (!data->dongles[i].heap)
            break;
        if (pthread_mutex_init(&data->dongles[i].mutex, NULL) != 0)
        {
            free(data->dongles[i].heap->arr);
            free(data->dongles[i].heap);
            break;
        }
        if (pthread_cond_init(&data->dongles[i].cond, NULL) != 0)
        {
            free(data->dongles[i].heap->arr);
            free(data->dongles[i].heap);
            pthread_mutex_destroy(&data->dongles[i].mutex);
            break;
        }
        i++;
    }
    if (i < data->n_coders)
    {
        while(i > 0)
        {   
            i--;
            if (data->dongles[i].heap)
            {
                free(data->dongles[i].heap->arr);
                free(data->dongles[i].heap);
            }
            pthread_mutex_destroy(&data->dongles[i].mutex);
            pthread_cond_destroy(&data->dongles[i].cond);
        }
        free(data->dongles);
        return (1);
    }
    return (0);
}
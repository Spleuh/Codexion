#include "codexion.h"

void    rollback_mutex_dong_cod(t_data *data, int n_dong, int n_cod)
{
    int i;

    i = -1;
    while (++i < n_dong)
        pthread_mutex_destroy(&data->dongles[i].mutex_dongle);
    i = -1;
    while (++i < n_cod)
        pthread_mutex_destroy(&data->coders[i].mutex_coder);
}

int     init_mutex_dong_cod(t_data *data)
{
    int i;

    i = -1;
    while (++i < data->n_coders)
    {
        if (pthread_mutex_init(&data->dongles[i].mutex_dongle, NULL) != 0)
        {
            rollback_mutex_dong_cod(data, i, i);
            return (1);
        }
        if (pthread_mutex_init(&data->coders[i].mutex_coders, NULL) != 0)
        {
            rollback_mutex_dong_cod(data, i+1, i);
            return (1);
        }
    }
    return (0);
}

int     init_mutex_print_state(t_data *data)
{
    if (pthread_mutex_init(&data->mutex_print, NULL) =! 0)
        return (1);
    if (pthread_mutex_init(&data->mutex_state_sim, NULL) =! 0)
    {
        pthread_mutex_destroy(&data->mutex_print);
        return (1);
    }
    return (0);
}

void    set_first_second_coders(t_data *data)
{
    int i;

    i = 0;
    while (i < data->n_coders)
    {
        if (data->dongles[i]->id < data->dongles[(i + 1) % data->n_coders]->id)
        {
            data->coders[i]->first = &data->dongles[i];
            data->coders[i]->second = &data->dongles[(i + 1) % data->n_coders];
        }
        else
        {
            data->coders[i]->second = &data->dongles[i];
            data->coders[i]->first = &data->dongles[(i + 1) % data->n_coders];
        }
        i++;
    }
}

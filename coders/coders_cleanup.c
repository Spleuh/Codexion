#include "codexion.h"

void    destroy_mutex_coders(t_coder *coders, int n)
{
    int i;

    i = 0;
    while (i < n)
    {
        pthread_mutex_destroy(&coders[i].mutex_coder);
        i++;
    }
}

void    cleanup_coders(t_data *data)
{
    destroy_mutex_coders(data->coders, data->n_coders);
    free(data->coders);
}
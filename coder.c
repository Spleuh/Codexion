#include "codexion.h"


void    free_coders(t_coder *coders, int i)
{
    while (i >= 0)
    {
        i--;
        pthread_mutex_destroy(&coders[i].mutex_coder);
    }
    free(coders);
}

t_coder *init_coders(t_data *data)
{
    int i;
    t_coder *coders;

    coders = malloc(sizeof(t_coder) * (data->args->n_coders));
    if (!coders)
        return (NULL);
    i = 0;
    while (i < data->args->n_coders)
    {
        coders[i].id = i;
        coders[i].data = data;
        coders[i].last_compile_start = 0;
        coders[i].compiles_done = 0;
        if (pthread_mutex_init(&coders[i].mutex_coder, NULL) != 0)
            break;
        i++;
    }
    if (i < data->args->n_coders)
    {
        free_coders(coders, i);
        return (NULL);
    }
    return (coders);
}
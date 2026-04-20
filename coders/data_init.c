#include "codexion.h"

void    init_args(t_data *data, char **argv)
{
    data->n_coders = atoi(argv[1]);
    data->t_burnout = atoi(argv[2]);
    data->t_compile = atoi(argv[3]);
    data->t_debug = atoi(argv[4]);
    data->t_refactor = atoi(argv[5]);
    data->n_compiles = atoi(argv[6]);
    data->t_cooldown = atoi(argv[7]);
    data->scheduler = 0;
    if (strcmp(argv[8], "edf") == 0)
        data->scheduler = 1;
    data->start_sim = 0;
    data->stop_sim = 0;
    data->cancel_sim = 0;
    data->count_ready = 0;
}

int     init_cond_data(t_data *data)
{    
    if (pthread_cond_init(&data->cond_start, NULL) != 0)
        return (1);
    if (pthread_cond_init(&data->cond_state_dongles, NULL) != 0)
    {
        pthread_cond_destroy(&data->cond_start);
        return (1);
    }
    return (0);
}

int     init_mutex_data(t_data *data)
{
    if (pthread_mutex_init(&data->mutex_print, NULL) != 0)
        return (1);
    if (pthread_mutex_init(&data->mutex_state_sim, NULL) != 0)
    {
        pthread_mutex_destroy(&data->mutex_print);
        return (1);
    }
    if (pthread_mutex_init(&data->mutex_state_dongles, NULL) != 0)
    {
        pthread_mutex_destroy(&data->mutex_print);
        pthread_mutex_destroy(&data->mutex_state_sim);
        return (1);
    }
    if (pthread_mutex_init(&data->mutex_ts_start, NULL) != 0)
    {
        pthread_mutex_destroy(&data->mutex_print);
        pthread_mutex_destroy(&data->mutex_state_sim);
        pthread_mutex_destroy(&data->mutex_state_dongles);
        return (1);

    }
    return (0);
}

int     init_mutex_cond_data(t_data *data)
{
    if (init_cond_data(data) != 0)
        return (1);
    if (init_mutex_data(data) != 0)
    {
        pthread_cond_destroy(&data->cond_start);
        pthread_cond_destroy(&data->cond_state_dongles);
        return (1);
    }
    return (0);
}

int     init_dongles_coders(t_data *data)
{
    if (init_dongles(data) != 0)
        return (1);
    if (init_coders(data) != 0)
    {
        cleanup_dongles(data);
        return (1);
    }
    return (0);
}

t_data  *init_data(char **argv)
{
    t_data  *data;

    data = malloc(sizeof(t_data));
    if (!data)
        return (NULL);
    init_args(data, argv);
    if (init_mutex_cond_data(data) != 0)
    {
        free(data);
        return (NULL);
    }
    if (init_dongles_coders(data) != 0)
    {
        destroy_mutex_cond_data(data);
        free(data);
        return (NULL);
    }
    if (init_mutex_cond_data(data) != 0)
    {
        destroy_mutex_cond_data(data);
        cleanup_dongles_coders(data);
        free(data);
        return (NULL);
    }
    return (data);
}
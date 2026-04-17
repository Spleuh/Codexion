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
    if (strcmp(argv[8], 'edf') == 0)
        data->scheduler = 1;
    data->start_sim = 0;
    data->stop_sim = 0;
    data->cancel_sim = 0;
    data->count_ready = 0;
}

int     init_dongles(t_data *data)
{
    t_dongle *dongles;
    int       i;

    dongles = malloc(sizeof(t_dongle) * args->n_coders);
    if (!dongles)
        return (1);
    i = 0;
    while (i < args->n_coders)
    {
        dongles[i].id = i;
        dongles[i].available = 1;
        dongles[i].id_priority = -1;
        dongles[i].end_cooldown = -1;
        i++;
    }
    data->dongles = dongles;
    return (0);
}

int     init_coders(t_data *data)
{
    int i;
    t_coder *coders;

    coders = malloc(sizeof(t_coder) * (data->args->n_coders));
    if (!coders)
        return (1);
    i = 0;
    while (i < data->args->n_coders)
    {
        coders[i].id = i;
        coders[i].data = data;
        coders[i].last_compile_start = 0;
        coders[i].compiles_done = 0;
        i++;
    }
    data->coders = coders;
    return (0);
}

int     init_mutex_cond_data(t_data *data)
{    
    if (init_mutex_dong_cod(data) != 0)
        return (1);
    if (pthread_cond_init(&data->cond_start, NULL) != 0)
    {
        rollback_mutex_dong_cod(data, data->n_coders, data->n_coders);
        return (1);
    }
    if (init_mutex_print_state(data) != 0)
    {
        rollback_mutex_dong_cod(data, data->n_coders, data->n_coders);
        pthread_cond_destroy(&data->cond_start);
        return (1)
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
    if (init_dongles(data) != 0 || init_coders(data) != 0 || init_mutex_cond_data(data) != 0)
    {
        free_data(data);
        return (NULL);
    }
    set_first_second_coders(data);
    return (data);
}
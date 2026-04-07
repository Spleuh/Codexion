#include "codexion.h"

void    lock_wait_dongles(t_dongle *dongle_left, t_dongle *dongle_right)
{
	int	check_left;
	int	check_right;

	check_left = (dongle_left->status && (dongle_left->reserved_for < 0 || dongle_left->reserved_for == args_cycle->id_coder));
	check_right = (dongle_right->status && (dongle_right->reserved_for < 0 || dongle_right->reserved_for == args_cycle->id_coder));

	pthread_mutex_lock(&dongle_left->mutex);
	pthread_mutex_lock(&dongle_right->mutex);
	if (check_left && check_right)
	{
		dongle_left->reserved_for == args_cycle->id_coder;
		dongle_left->status = 0;
	}
    return ;
}

void    cycle_coder(t_args_cycle *args_cycle)
{
	t_dongle *dongle_left;
	t_dongle *dongle_right;

	dongle_left = args_cycle->dongles[args_cycle->id_coder];
	dongle_right = args_cycle->dongles[(args_cycle->id_coder + 1) % args_cycle->data->n_coders];
    while(!stop_sim)
    {


    }
}

t_args_cycle    *get_args_cycle(int  id_coder, t_data *data, t_dongle *dongles)
{
    t_args_cycle *args_cycle;

    args_cycle = malloc(sizeof(t_args_cycle));
    if (!args_cycle)
        return (NULL);
    args_cycle->id_coder = id_coder;
    args_cycle->dongles = dongles;
    args_cycle->data = data;
    return args_cycle;
}

t_coder   *init_coders(t_data *data, t_dongle *dongles)
{
    pthread_t   *coders;
    t_args_cycle    *args_cycle;
    int         i;

    i = 0;
    n_coders = data->n_coders;
    coders = malloc(sizeof(pthread_t) * data->n_coders);
	if (!coders)
		return 1;
    while(i < data->n_coders)
    {
        coders[i]->id = i;
        coders[i]->last_compile = 0;
		args_cycle = get_args_cycle(i, data, dongles);
        pthread_create(&(coders[i]->thread), NULL, cycle_coder, args_cycle);
        i++;
    }
	return coders;
}
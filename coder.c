#include "codexion.h"

void    compile(t_args_cycle *args_cycle)
{
	int	check_left;
	int	check_right;

    while(1)
    {
	    pthread_mutex_lock(&dongle_left->mutex_decision);
	    pthread_mutex_lock(&dongle_right->mutex_decision);
	    check_left = (dongle_left->status && (dongle_left->reserved_for < 0 || dongle_left->reserved_for == args_cycle->id_coder));
	    check_right = (dongle_right->status && (dongle_right->reserved_for < 0 || dongle_right->reserved_for == args_cycle->id_coder));
        if (check_left && check_right)
        {

        }
        else
        {
            pthread_mutex_unlock(&dongle_left->mutex_decision);
	        pthread_mutex_unlock(&dongle_right->mutex_decision);
        }

    }

    while(!check_left || !check_right)
    {
        pthread_cond_wait()
    }
	if (check_left && check_right)
	{
		dongle_left->reserved_for == args_cycle->id_coder;
		dongle_left->status = 0;
	}
    else
    {
        pthread_cond_wait()
    }

    return ;
}

void    cycle_coder(t_args_cycle *args_cycle)
{
    while(!args_cycle->stop_sim)
    {
        lock_wait_dongles(args_cycle);
    }
}

t_args_cycle    *get_args_cycle(int  id_coder, t_data *data, t_dongle *dongles)
{
    t_args_cycle *args_cycle;

    args_cycle = malloc(sizeof(t_args_cycle));
    if (!args_cycle)
        return (NULL);
    args_cycle->id_coder = id_coder;
    args_cycle->dongles_left = dongles[id_coder];
    args_cycle->dongles_right = dongles[(id_coder + 1) % data->n_coders];
    args_cycle->mutex_global = data->mutex_global;
    args_cycle->stop_sim = &data->stop_sim;
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsam <jsam@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 19:05:47 by jsam              #+#    #+#             */
/*   Updated: 2026/04/21 19:05:50 by jsam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	init_args(t_data *data, char **argv)
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

int	init_dongles_coders(t_data *data)
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

t_data	*init_data(char **argv)
{
	t_data	*data;

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
	return (data);
}

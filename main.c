/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsam <jsam@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 10:20:52 by jsam              #+#    #+#             */
/*   Updated: 2026/04/06 00:30:15 by jsam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <unistd.h>

void	free_data(t_data *data)
{
	pthread_mutex_destroy(&data->mutex_print);
	pthread_mutex_destroy(&data->mutex_start);
	pthread_mutex_destroy(&data->mutex_stop);
	pthread_cond_destroy(&data->cond_start);
	free_dongles(data->dongles, data->n_coders);
	free(data->scheduler);
	if (data)
		free(data);
}

int	main(int argc, char **argv)
{
	t_coder *coders;
	t_data	*data;
	
	data = store_data(argc, argv);
	if (!data)
		return 1;
	coders = malloc(sizeof(t_coder) * data->n_coders);
	if (!coders)
		return 1;
	init_coders(coders, data);
	init_monitor(coders);
	pthread_mutex_lock(&data->mutex_start);
    data->start_sim = 1;
    pthread_mutex_unlock(&data->mutex_start);
    pthread_cond_broadcast(&data->cond_start);

	int	i;
	i = 0;
	while(i < data->n_coders)
	{
		pthread_join(coders[i].thread, NULL);
		i++;
	}
	pthread_join(data->monitor, NULL);
	usleep(1000);
	free(coders);
	free_data(data);
	return 0;
}

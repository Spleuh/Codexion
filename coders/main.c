/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsam <jsam@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 21:39:34 by jsam              #+#    #+#             */
/*   Updated: 2026/04/13 21:39:37 by jsam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "codexion.h"

void	wait_ready_start(t_data *data)
{
	pthread_mutex_lock(&data->mutex_state_sim);
	while (data->count_ready < data->n_coders + 1)
		pthread_cond_wait(&data->cond_start, &data->mutex_state_sim);
	data->start_sim = 1;
	pthread_cond_broadcast(&data->cond_start);
	pthread_mutex_unlock(&data->mutex_state_sim);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (parser(argc, argv))
		return (1);
	data = init_data(argv);
	if (!data)
		return (1);
	// if (create_thread_all(data) != 0)
	// 	return (1);

	// create_thread_all(data);
	// wait_ready_start(data);
	// join_thread_all(data);
	cleanup_data(data);
	return (0);
}

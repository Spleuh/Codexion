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

int	main(int argc, char **argv)
{
	t_data	*data;
	if (parser(argc, argv))
		return (1);
	data = init_data(argv);
	if (!data)
		return (1);
	if (create_thread_coders(data) != 0)
	{
		free_data(data);
		return (1);
	}
	create_thread_coders(data);
	pthread_create(&data->thread_monitor, NULL, routine_monitor, data);
	while (get_count_ready(data) < data->n_coders + 1)
	{
		
	}


	// create_thread_coders(data->coders);
	// pthread_create(&monitor->thread_monitor, NULL, routine_monitor, monitor);
	// pthread_create(&scheduler->thread_scheduler, NULL, routine_scheduler, scheduler);

	// set_start_sim(data, 1);
	// pthread_cond_broadcast(&data->cond_start);

	// join_thread_coders(data->coders, data->args->n_coders);
	// pthread_join(monitor->thread_monitor, NULL);
	// pthread_join(scheduler->thread_scheduler, NULL);

	// free(scheduler);
	// free(monitor);
	// free_data(data);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles_cleanup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsam <jsam@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 19:06:19 by jsam              #+#    #+#             */
/*   Updated: 2026/04/21 19:06:20 by jsam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	destroy_mutex_dongles(int i, t_dongle *dongles)
{
	i--;
	while (i >= 0)
	{
		pthread_mutex_destroy(&dongles[i].mutex_dongle);
		i--;
	}
}

void	free_queue_dongles(int n, t_dongle *dongles)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(dongles[i].queue->tree);
		free(dongles[i].queue);
		i++;
	}
}

void	cleanup_dongles(t_data *data)
{
	destroy_mutex_dongles(data->n_coders, data->dongles);
	free_queue_dongles(data->n_coders, data->dongles);
	free(data->dongles);
}

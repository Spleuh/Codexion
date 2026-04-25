/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsam <jsam@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 19:04:49 by jsam              #+#    #+#             */
/*   Updated: 2026/04/21 19:04:51 by jsam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	destroy_mutex_cond_data(t_data *data)
{
	pthread_mutex_destroy(&data->mutex_print);
	pthread_mutex_destroy(&data->mutex_state_sim);
	pthread_mutex_destroy(&data->mutex_state_dongles);
	pthread_cond_destroy(&data->cond_start);
	pthread_cond_destroy(&data->cond_state_dongles);
	return ;
}

void	cleanup_dongles_coders(t_data *data)
{
	if (data->dongles)
		cleanup_dongles(data);
	if (data->coders)
		cleanup_coders(data);
}

void	cleanup_data(t_data *data)
{
	destroy_mutex_cond_data(data);
	cleanup_dongles_coders(data);
	free(data);
}

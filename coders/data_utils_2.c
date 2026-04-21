/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsam <jsam@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 19:06:06 by jsam              #+#    #+#             */
/*   Updated: 2026/04/21 19:06:09 by jsam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	get_stop_sim(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->mutex_state_sim);
	result = data->stop_sim;
	pthread_mutex_unlock(&data->mutex_state_sim);
	return (result);
}

void	set_stop_sim(t_data *data, int i)
{
	pthread_mutex_lock(&data->mutex_state_sim);
	data->stop_sim = i;
	pthread_mutex_unlock(&data->mutex_state_sim);
}

void	incr_count_ready(t_data *data)
{
	pthread_mutex_lock(&data->mutex_state_sim);
	data->count_ready++;
	pthread_mutex_unlock(&data->mutex_state_sim);
}

void	set_start_sim(t_data *data, int i)
{
	pthread_mutex_lock(&data->mutex_state_sim);
	data->start_sim = i;
	pthread_cond_broadcast(&data->cond_start);
	pthread_mutex_unlock(&data->mutex_state_sim);
}

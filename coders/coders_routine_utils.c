/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders_routine_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsam <jsam@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 19:04:33 by jsam              #+#    #+#             */
/*   Updated: 2026/04/21 19:04:35 by jsam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	unlock_dongles(t_coder *coder)
{
	pthread_mutex_unlock(&coder->second->mutex_dongle);
	pthread_mutex_unlock(&coder->first->mutex_dongle);
}

void	try_lock_dongles(t_coder *coder)
{
	if (coder->first == coder->second)
		return ;
	if (pthread_mutex_lock(&coder->first->mutex_dongle) != 0)
		return ;
	else if (pthread_mutex_lock(&coder->second->mutex_dongle) != 0)
	{
		pthread_mutex_unlock(&coder->first->mutex_dongle);
		return ;
	}
}

int	check_priority(t_coder *coder)
{
	if (coder->first->available == 0)
		return (1);
	else if (coder->first->available == 0)
		return (1);
	else if (get_id_priority(coder->first->queue) != coder->id)
		return (1);
	else if (get_id_priority(coder->second->queue) != coder->id)
		return (1);
	else if (coder->first->end_cooldown > get_timestamp(coder->data))
		return (1);
	else if (coder->second->end_cooldown > get_timestamp(coder->data))
		return (1);
	return (0);
}

int	update_cd_dongles(t_coder *coder)
{
	long	new_cd;

	pthread_mutex_lock(&coder->data->mutex_state_dongles);
	new_cd = get_timestamp(coder->data) + coder->data->t_cooldown;
	coder->first->end_cooldown = new_cd;
	coder->second->end_cooldown = new_cd;
	pthread_mutex_unlock(&coder->data->mutex_state_dongles);
	return (0);
}

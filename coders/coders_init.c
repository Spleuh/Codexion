/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsam <jsam@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 19:03:59 by jsam              #+#    #+#             */
/*   Updated: 2026/04/21 19:04:03 by jsam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	init_args_coders(t_coder *coders, int n, t_data *data)
{
	int	i;

	i = 0;
	while (i < n)
	{
		coders[i].id = i;
		coders[i].compiles_done = 0;
		coders[i].last_compile_start = 0;
		coders[i].data = data;
		i++;
	}
}

int	init_mutex_coders(t_coder *coders, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (pthread_mutex_init(&coders[i].mutex_coder, NULL) != 0)
		{
			destroy_mutex_coders(coders, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	set_first_second_coders(t_coder *coders, t_dongle *dongles, int n)
{
	int	i;

	if (!coders || !dongles)
		return (1);
	i = 0;
	while (i < n)
	{
		if (dongles[i].id < dongles[(i + 1) % n].id)
		{
			coders[i].first = &dongles[i];
			coders[i].second = &dongles[(i + 1) % n];
		}
		else
		{
			coders[i].second = &dongles[i];
			coders[i].first = &dongles[(i + 1) % n];
		}
		i++;
	}
	return (0);
}

int	init_coders(t_data *data)
{
	data->coders = malloc(sizeof(t_coder) * data->n_coders);
	if (!data->coders)
		return (1);
	if (set_first_second_coders(data->coders, data->dongles, data->n_coders)
		!= 0)
	{
		free(data->coders);
		return (1);
	}
	init_args_coders(data->coders, data->n_coders, data);
	if (init_mutex_coders(data->coders, data->n_coders) != 0)
	{
		free(data->coders);
		return (1);
	}
	return (0);
}

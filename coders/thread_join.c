/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsam <jsam@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 19:07:37 by jsam              #+#    #+#             */
/*   Updated: 2026/04/21 19:07:40 by jsam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	join_thread_coders(t_data *data, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join(data->coders[i].thread_coder, NULL);
		i++;
	}
}

void	join_thread_all(t_data *data)
{
	join_thread_coders(data, data->n_coders);
	pthread_join(data->thread_monitor, NULL);
}

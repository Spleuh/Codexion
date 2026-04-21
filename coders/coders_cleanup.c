/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsam <jsam@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 19:03:40 by jsam              #+#    #+#             */
/*   Updated: 2026/04/21 19:03:47 by jsam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	destroy_mutex_coders(t_coder *coders, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&coders[i].mutex_coder);
		i++;
	}
}

void	cleanup_coders(t_data *data)
{
	destroy_mutex_coders(data->coders, data->n_coders);
	free(data->coders);
}

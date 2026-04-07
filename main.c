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

#include <stdio.h>
#include "codexion.h"
#include <unistd.h>

int	main(int argc, char **argv)
{
	pthread_t *coders;
	t_data	*data;

	data = store_data(argc, argv);
	if (!data)
		return (1);
	coders = malloc(sizeof(pthread_t) * data->n_coders);
	if (!coders)
		return 1;

	printf("%d\n", data->t_cooldown);
	free(coders);
	return 0;
}

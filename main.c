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
	t_scheduler *scheduler;
	t_monitor	*monitor;
	if (parser(argc, argv))
		return (1);
	data = init_data(argv);
	if (!data)
		return (1);
	scheduler = init_scheduler(data);
	monitor = init_monitor(data);
	(void)scheduler;
	(void)monitor;
	free(data);
	return (0);
}
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
	{
		printf("Error: n_coder > 1, scheduler 'fifo' or 'edf' and other > 0\n");
		return (1);
	}
	data = init_data(argv);
	if (!data)
		return (1);
	if (create_thread_all(data) != 0)
		return (1);
	wait_ready_start(data);
	join_thread_all(data);
	cleanup_data(data);
	return (0);
}

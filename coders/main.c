/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsam <jsam@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 21:39:34 by jsam              #+#    #+#             */
/*   Updated: 2026/04/21 21:43:17 by jsam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (parser(argc, argv))
	{
		printf("Error: n_coder and n_compile >= 1, ");
		printf("scheduler 'fifo' or 'edf' and other >= 0\n");
		return (0);
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

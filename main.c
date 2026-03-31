/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsam <jsam@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 10:20:52 by jsam              #+#    #+#             */
/*   Updated: 2026/03/31 10:49:31 by jsam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "codexion.h"

void	*thread_cycle(void *arg)
{
	mutex_data	*md;
	int			*i;

	md = (mutex_data *) arg;
	i = (int *) arg;
	(*i)++;
	pthread_exit(NULL);
}

int	main(void)
{
	t_mutex_dongle	md;
	pthread_t		*coder;

	md.data = 0;
	if (pthread_mutex_init(&md.mutex, NULL) != 0)
	{
		printf("fail ini nutex\n");
		return (1);
	}

	err = pthread_create(&coder, NULL, thread_cycle, &md)

	if (err != 0)
	{
		printf("creation thread failed")
		return (1)
	}

	return (0);
}
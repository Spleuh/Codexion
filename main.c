/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsam <jsam@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 10:20:52 by jsam              #+#    #+#             */
/*   Updated: 2026/03/31 15:29:15 by jsam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "codexion.h"
#include <unistd.h>

#define N_THREAD 5
#define INCREMENTS 1000

int counter = 0;
pthread_mutex_t counter_mutex;

void *increment(void *arg)
{
	while (counter < INCREMENTS)
	{
		pthread_mutex_lock(&counter_mutex);
		counter++;
		pthread_mutex_unlock(&counter_mutex);
	}
	return NULL;
}

int	main()
{
	pthread_t *threads;
	int i;

	i = 0;
	threads = malloc(sizeof(pthread_t) * N_THREAD);
	if (!threads)
		return 1;

	pthread_mutex_init(&counter_mutex, NULL);

	while (i < N_THREAD)
	{
		pthread_create(&threads[i], NULL, increment, NULL);
		i++;
	}
	i = 0;
	while (i < N_THREAD)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&counter_mutex);

	printf("%d\n", counter);
	free(threads);
	return 0;
}
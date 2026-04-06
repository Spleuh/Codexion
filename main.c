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
#include <stdlib.h>
#include <pthread.h>
#include "codexion.h"
#include <unistd.h>
#include <string.h>

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

void	cycle_coder(int n_compiles, t_coder *coder, t_dongle *dongle_1, t_dongle *dongle_2)
{
	int	i;

	i = 0;
	while (i < n_compiles)
	{

		i++;
	}
}

int check_arg_int(int time, int min)
{
	if (time < min || time > 2147483647)
		return -1;
	return 0;
}

int check_int(char *arg)
{
	int i;
	
	i = 0;
	if (!arg)
		return -1;	
	while (arg[i])
	{
		if (arg[i] < 30 || arg[i] > 39)
			return -1;
		i++;
	}
	return 0;
}



int	parser(int argc, char **argv)
{
	int i;
	int *converted;
	int result;

	result = 0;
	converted = malloc(sizeof(int) * 7);
	if (!converted)
		return -1;
	if (argc != 9)
		return -1;
	i = 1;
	while(i < 8 && !result)
	{
		if (!check_int(argv[i]))
			return -1;
		converted[i - 1] = atoi(argv[i]);	
		if (!converted[i - 1])
			result = -1;
		i++;
	}
	if (!result && check_arg_int(converted[0], 2) < 0)
		result = -1;
	i = 1;
	while (!result && !check_arg_int(converted[i], 1) && i < 7)
		i++;
	free(converted);
	if (!result && i != 7)
		result = -1;
	if (!result && strcmp(argv[8], "fifo") != 0 && strcmp(argv[8], "edf") != 0)
		result = -1;
	return result;
}

t_data	*store_data(char **argv)
{
	t_data	*data;

	if (!*argv)
		return (NULL);
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->n_coders = atoi(argv[1]);
	data->t_burnout = atoi(argv[2]);
	data->t_compile = atoi(argv[3]);
	data->t_debug = atoi(argv[4]);
	data->t_refactor = atoi(argv[5]);
	data->n_compiles = atoi(argv[6]);
	data->t_cooldown = atoi(argv[7]);
	data->scheduler = argv[8];
	return (data);
}

int	main(int argc, char **argv)
{
	pthread_t *threads;
	t_data	*data;
	pthread_mutex	global;
	int i;

	i = 0;

	if (parser(argc, argv) < 0)
	{
		printf("ERROR");
		return (1);
	}
	data = store(**argv);
	if (!data)
		return (1);
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

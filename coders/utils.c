/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsam <jsam@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 05:47:40 by jsam              #+#    #+#             */
/*   Updated: 2026/04/14 05:47:43 by jsam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdarg.h>


void    print_mutex(t_data *data, char *str, int id)
{
    long    ts;
    pthread_mutex_lock(&data->mutex_print);
    if (get_stop_sim(data))
    {
        pthread_mutex_unlock(&data->mutex_print);
        return ;
    }
    ts = get_timestamp(data);
    printf("%ld %d %s\n",ts , id + 1, str);
    pthread_mutex_unlock(&data->mutex_print);
}

void    print_stop_burned_out(t_data *data, int id)
{
    long    ts;

    ts = get_timestamp(data);
    pthread_mutex_lock(&data->mutex_print);
    pthread_mutex_lock(&data->mutex_state_sim);
    data->stop_sim = 1;
    printf("%ld %d burned out\n", ts, id);
    pthread_mutex_unlock(&data->mutex_state_sim);
    pthread_mutex_unlock(&data->mutex_print);
}

void	wait_ready_start(t_data *data)
{
    while (get_count_ready(data) < data->n_coders + 1)
    {
        usleep(100);
    }
    pthread_mutex_lock(&data->mutex_state_sim);
	data->start_sim = 1;
    data->ts_start = 0;
    data->ts_start = get_timestamp(data);
	pthread_cond_broadcast(&data->cond_start);
	pthread_mutex_unlock(&data->mutex_state_sim);
}

void    wait_ready_end(t_data *data)
{
    while (get_count_ready(data) > 0)
    {
        send_broadcast_state_dongle(data);
        usleep(1000);
    }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsam <jsam@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 05:48:16 by jsam              #+#    #+#             */
/*   Updated: 2026/04/14 05:48:17 by jsam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int     get_count_ready(t_data *data)
{
    int result;

    pthread_mutex_lock(&data->mutex_state_sim);
    result = data->count_ready;
    pthread_mutex_unlock(&data->mutex_state_sim);
    return (result);
}

long    get_ts_start(t_data *data)
{
    long    ts_start;
    
    pthread_mutex_lock(&data->mutex_ts_start);
    ts_start = data->ts_start;
    pthread_mutex_unlock(&data->mutex_ts_start);
    return (ts_start);
}

long    get_timestamp(t_data *data)
{
    long    result;
    struct  timeval time;
    gettimeofday(&time, NULL);
    result = time.tv_sec * 1000L + time.tv_usec / 1000L;
    result = result - get_ts_start(data);
    return (result);
}

int     get_cancel_sim(t_data *data)
{
    int result;

    pthread_mutex_lock(&data->mutex_state_sim);
    result = data->cancel_sim;
    pthread_mutex_unlock(&data->mutex_state_sim);
    return (result);
}

void    set_cancel_sim(t_data *data, int i)
{
    pthread_mutex_lock(&data->mutex_state_sim);
    data->cancel_sim = i;
    pthread_mutex_unlock(&data->mutex_state_sim);
}

void    set_start_sim(t_data *data, int i)
{
    pthread_mutex_lock(&data->mutex_state_sim);
    data->start_sim = i;
    pthread_cond_broadcast(&data->cond_start);
    pthread_mutex_unlock(&data->mutex_state_sim);
}

void    print_debug(char *i)
{
    printf("%s\n", i);
}

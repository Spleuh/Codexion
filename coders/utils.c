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

long    get_timestamp(t_data *data)
{
    long    result;
    struct  timeval time;
    gettimeofday(&time, NULL);
    
    result = time.tv_sec * 1000L + time.tv_usec / 1000L
    result -= data->ts_start;
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

void    cancel_sim(t_data *data)
{
    pthread_mutex_lock(&data->mutex_state_sim);
    data->cancel_sim = 1;
    pthread_mutex_unlock(&data->mutex_state_sim);
}

void    start_sim(t_data *data)
{
    pthread_mutex_lock(&data->mutex_state_sim);
    data->start_sim = 1;
    pthread_cond_broadcast(&data->cond_start);
    pthread_mutex_unlock(&data->mutex_state_sim);
}

void    print_debug(char *i)
{
    printf("%s\n", i);
}

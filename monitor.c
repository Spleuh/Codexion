/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsam <jsam@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 05:47:25 by jsam              #+#    #+#             */
/*   Updated: 2026/04/14 05:47:28 by jsam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int         get_stop_sim(t_data *data)
{
    int result;

    pthread_mutex_lock(&data->mutex_env->mutex_state_sim);
    result = data->stop_sim;
    pthread_mutex_unlock(&data->mutex_env->mutex_state_sim);
    return (result);
}
void    set_stop_sim(t_data *data, int i)
{
    pthread_mutex_lock(&data->mutex_env->mutex_state_sim);
    data->stop_sim = i;
    pthread_mutex_unlock(&data->mutex_env->mutex_state_sim);
}


t_monitor   *init_monitor(t_data *data)
{
    t_monitor *monitor;

    monitor = malloc(sizeof(t_monitor));
    if (!monitor)
        return (NULL);
    monitor->coders = data->coders;
    monitor->data= data;
    return (monitor);
}



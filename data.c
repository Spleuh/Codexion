/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsam <jsam@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 21:49:20 by jsam              #+#    #+#             */
/*   Updated: 2026/04/13 21:49:24 by jsam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "codexion.h"

int     init_cond_data(t_data *data)
{
    if (pthread_cond_init(&data->cond_entry, NULL) != 0)
        return (1);
    if (pthread_cond_init(&data->cond_start, NULL) != 0)
    {
        pthread_cond_destroy(&data->cond_entry);
        return (1);
    }
    return (0);
}

int     get_start_sim(t_data *data)
{
    int result;

    if (get_stop_sim(data))
        return (0);
    pthread_mutex_lock(&data->mutex_env->mutex_state_sim);
    result = data->start_sim;
    pthread_mutex_unlock(&data->mutex_env->mutex_state_sim);
    return (result);
}

void    set_start_sim(t_data *data, int i)
{
    if (get_stop_sim(data))
        return ;
    pthread_mutex_lock(&data->mutex_env->mutex_state_sim);
    data->start_sim = i;
    pthread_mutex_unlock(&data->mutex_env->mutex_state_sim);
}



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
    pthread_mutex_lock(&data->mutex_print);
    if (get_stop_sim(data))
    {
        pthread_mutex_unlock(&data->mutex_env->mutex_print);
        return ;
    }
    printf("%ld %d %s\n", get_timestamp(), id, str);
    pthread_mutex_unlock(&data->mutex_env->mutex_print);
}

void    print_stop_burned_out(t_data *data, int id)
{
    pthread_mutex_lock(&data->mutex_print);
    pthread_mutex_lock(&data->mutex_state_sim);
    data->stop_sim = 1;
    printf("%ld %d burned out\n", get_timestamp(), id);
    pthread_mutex_unlock(&data->mutex_state_sim);
    pthread_mutex_unlock(&data->mutex_print);
}

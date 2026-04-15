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
    long    timestamp;

    timestamp = get_timestamp() - data->timestamp_start;
    pthread_mutex_lock(&data->mutex_env->mutex_print);
    printf("%ld %d %s\n", timestamp, id, str);
    pthread_mutex_unlock(&data->mutex_env->mutex_print);
}

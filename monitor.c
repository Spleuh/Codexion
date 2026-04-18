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



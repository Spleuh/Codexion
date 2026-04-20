/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsam <jsam@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 05:47:11 by jsam              #+#    #+#             */
/*   Updated: 2026/04/14 05:47:20 by jsam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void    set_available(t_data *data, t_dongle *dongle, int i)
{
    pthread_mutex_lock(&data->mutex_state_dongles);
    dongle->available = i;
    pthread_mutex_unlock(&data->mutex_state_dongles);
}


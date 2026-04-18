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

// void    set_end_cooldown(t_dongle *dongle, long timestamp)
// {
//     pthread_mutex_lock(&dongle->mutex_dongle);
//     dongle->end_cooldown = timestamp;
//     pthread_mutex_unlock(&dongle->mutex_dongle);
// }

long    get_end_cooldown(t_dongle *dongle)
{
    long    result;

    pthread_mutex_lock(&dongle->mutex_dongle);
    result = dongle->end_cooldown;
    pthread_mutex_unlock(&dongle->mutex_dongle);
    return (result);

}

int     get_available(t_dongle *dongle)
{
    int result;
    pthread_mutex_lock(&dongle->mutex_dongle);
    result = dongle->available;
    pthread_mutex_unlock(&dongle->mutex_dongle);
    return (result);
}

int     check_available(int id_coder, t_dongle *first, t_dongle *second)
{
    (void)id_coder;
    int result;
    
    result = 1;
    if (get_available(first) == 0)
        result = 0;
    else if (get_available(second) == 0)
        result = 0;
    return (result);
}

void    set_available(t_dongle *dongle, int i)
{
    pthread_mutex_lock(&dongle->mutex_dongle);
    dongle->available = i;
    pthread_mutex_unlock(&dongle->mutex_dongle);
}


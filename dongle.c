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

void    set_end_cooldown(t_dongle *dongle, long timestamp)
{
    pthread_mutex_lock(&dongle->mutex_dongle);
    dongle->end_cooldown = timestamp;
    pthread_mutex_unlock(&dongle->mutex_dongle);
}

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

int     get_id_priority(t_dongle *dongle)
{
    int result;

    pthread_mutex_lock(&dongle->mutex_dongle);
    result = dongle->id_priority;
    pthread_mutex_unlock(&dongle->mutex_dongle);
    return (result);
}

int     check_id_priority(int id_coder, t_dongle *first, t_dongle *second)
{
    (void)id_coder;
    if (!get_id_priority(first) || !get_id_priority(second))
        return (0);
    return (1);
}

void    set_available(t_dongle *dongle, int i)
{
    pthread_mutex_lock(&dongle->mutex_dongle);
    dongle->available = i;
    pthread_mutex_unlock(&dongle->mutex_dongle);
}

void    free_dongles(int i, t_dongle *dongles)
{
    destroy_mutex_dongles(i, dongles);
    free(dongles);
}

void    destroy_mutex_dongles(int i, t_dongle *dongles)
{
    i--;
    while (i >= 0)
    {
        
        pthread_mutex_destroy(&dongles->mutex_dongle);
        i--;
    }
}

int     init_mutex_dongles(t_dongle *dongles, int n)
{
    int i;

    i = 0;
    while (i < n)
    {

        if (pthread_mutex_init(&dongles[i].mutex_dongle, NULL) != 0)
            return (i++);
        i++;
    }
    return (0);
}
t_dongle    *init_dongles(t_args *args)
{
    t_dongle *dongles;
    int       i;

    dongles = malloc(sizeof(t_dongle) * args->n_coders);
    if (!dongles)
        return (NULL);
    i = 0;
    while (i < args->n_coders)
    {
        dongles[i].id = i;
        dongles[i].available = 1;
        dongles[i].id_priority = -1;
        dongles[i].end_cooldown = -1;
        i++;
    }
    return (dongles);
}

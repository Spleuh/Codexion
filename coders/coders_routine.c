/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_coder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsam <jsam@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 05:47:49 by jsam              #+#    #+#             */
/*   Updated: 2026/04/14 05:47:51 by jsam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"



void    take_dongles(t_coder *coder)
{
    if (get_stop_sim(coder->data))
        return ;
    add_requests(coder);
    pthread_mutex_lock(&coder->data->mutex_state_dongles);
    while (get_stop_sim(coder->data) && check_priority(coder) != 0)
        pthread_cond_wait(&coder->data->cond_state_dongles, &coder->data->mutex_state_dongles);
    if (get_stop_sim(coder->data))
    {
        pthread_mutex_unlock(&coder->data->mutex_state_dongles);
        return ;
    }
    coder->first->available = 0;
    coder->second->available = 0;
    remove_requests(coder);
    pthread_cond_broadcast(&coder->data->cond_state_dongles);
    pthread_mutex_unlock(&coder->data->mutex_state_dongles);
    try_lock_dongles(coder);
    print_mutex(coder->data, "has taken dongle", coder->id);
    print_mutex(coder->data, "has taken dongle", coder->id);
}

void    compile(t_coder *coder)
{
    print_mutex(coder->data, "is compiling", coder->id);
    set_last_compile(coder, get_timestamp(coder->data));
    if (get_stop_sim(coder->data))
    {
        unlock_dongles(coder);
        return ;
    }
    usleep(coder->data->t_compile * 1000);
    incr_compile_done(coder);
    update_cd_dongles(coder);
    set_available(coder->data, coder->first, 1);
    set_available(coder->data, coder->second, 1);
    pthread_mutex_lock(&coder->data->mutex_state_dongles);
    pthread_cond_broadcast(&coder->data->cond_state_dongles);
    pthread_mutex_unlock(&coder->data->mutex_state_dongles);
    unlock_dongles(coder);
}

void    debug(t_coder *coder)
{
    if (get_stop_sim(coder->data))
        return ;
    print_mutex(coder->data, "is debugging", coder->id);
    usleep(coder->data->t_debug * 1000);
}

void    refactor(t_coder *coder)
{
    if (get_stop_sim(coder->data))
        return ;
    print_mutex(coder->data, "is refactoring", coder->id);
    usleep(coder->data->t_refactor * 1000);
}


void    *routine_coder(void *arg)
{
    t_coder *coder;
    
    coder = (t_coder *)arg;
    incr_count_ready(coder->data);
    pthread_mutex_lock(&coder->data->mutex_state_sim);
    while (coder->data->start_sim == 0)
        pthread_cond_wait(&coder->data->cond_start, &coder->data->mutex_state_sim);
    pthread_mutex_unlock(&coder->data->mutex_state_sim);
    if (get_cancel_sim(coder->data))
        return (NULL);
    while (get_stop_sim(coder->data) == 0)
    {
        take_dongles(coder);
        compile(coder);
        debug(coder);
        refactor(coder);
    }
    decr_count_ready(coder->data);
    return (NULL);
}

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


int (*get_scheduler(char* schedule))(int, t_dongle*, t_dongle*)
{
    if (strcmp(schedule, "fifo") == 0)
        return (&check_available);
    else if (strcmp(schedule, "edf") == 0)
        return (&check_id_priority);
    return (NULL);
}



void    unlock_mutex_dongles(t_dongle *first, t_dongle *second)
{
    pthread_mutex_unlock(&first->mutex_dongle);
    pthread_mutex_unlock(&second->mutex_dongle);
}


void    take_dongles(t_coder *coder)
{
    long    new_cd;

    if (get_stop_sim(coder->data))
        return ;
    pthread_mutex_lock(&coder->data->mutex_state_dongles);
    add_requests(coder);
    while (check_priority(coder) != 0)
        pthread_cond_wait(&coder->data->cond_state_dongles, &coder->data->mutex_state_dongles);
    new_cd = get_timestamp() - coder->data->timestamp_start + coder->data->args->t_cooldown;
    new_cd = new_cd + coder->data->t_compile;
    first->end_cooldown = new_cd;
    second->end_cooldown = new_cd;
    pthread_mutex_lock(&first->mutex_dongle);
    pthread_mutex_lock(&second->mutex_dongle);
    pthread_mutex_unlock(&coder->data->mutex_state_dongles);
    print_mutex(coder->data, "has taken dongle", coder->id);
    print_mutex(coder->data, "has taken dongle", coder->id);
}

void    compile(t_coder *coder, t_dongle *first, t_dongle *second)
{

    if (get_stop_sim(coder->data))
        return ;
    print_mutex(coder->data, "is compiling", coder->id);
    set_last_compile(coder,get_timestamp() - coder->data->timestamp_start);
    usleep(coder->data->args->t_compile * 1000);
    incr_compile_done(coder);
    pthread_mutex_unlock(&first->mutex_dongle);
    pthread_mutex_unlock(&second->mutex_dongle);
}

void    debug(t_coder *coder)
{
    if (get_stop_sim(coder->data))
        return ;
    print_mutex(coder->data, "is debugging", coder->id);
    usleep(coder->data->args->t_debug * 1000);
}

void    refactor(t_coder *coder)
{
    if (get_stop_sim(coder->data))
        return ;
    print_mutex(coder->data, "is refactoring", coder->id);
    usleep(coder->data->args->t_refactor * 1000);
}


void    *routine_coder(void *arg)
{
    t_coder *coder;
    
    coder = (t_coder *)arg;
    pthread_mutex_lock(&coder->data->mutex_state_sim);
    while (!coder->data->start_sim)
            pthread_cond_wait(&coder->data->cond_start, &coder->data->mutex_state_sim);
    pthread_mutex_unlock(&coder->data->mutex_env->mutex_state_sim);
    if (get_cancel_sim(coder->data))
        return (NULL);
    while (!get_stop_sim(coder->data))
    {
        take_dongles(coder, first, second);
        compile(coder, first, second);
        debug(coder);
        refactor(coder);
    }
    return (NULL);
}

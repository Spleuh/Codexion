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

int     lock_mutex_dongles(t_dongle *first, t_dongle *second)
{
    if (pthread_mutex_lock(&first->mutex_dongle) != 0)
        return (1);
    if (pthread_mutex_lock(&second->mutex_dongle) != 0)
    {
        pthread_mutex_unlock(&first->mutex_dongle);
        return (1);
    }
    return (0);
}

void    unlock_mutex_dongles(t_dongle *first, t_dongle *second)
{
    pthread_mutex_unlock(&first->mutex_dongle);
    pthread_mutex_unlock(&second->mutex_dongle);
}


void    take_dongles(t_coder *coder, t_dongle *first, t_dongle *second)
{
    int (*f)(int, t_dongle*, t_dongle*);

    if (get_stop_sim(coder->data))
        return ;
    f = get_scheduler(coder->data->args->schedule);
    pthread_mutex_lock(&coder->data->mutex_env->mutex_schedule);

    while(1)
    {
        if (get_stop_sim(coder->data))
        {
            pthread_mutex_unlock(&coder->data->mutex_env->mutex_schedule);
            return ;
        }
        while (!f(coder->id, first, second))
        {
            pthread_cond_wait(&coder->data->cond_entry, &coder->data->mutex_env->mutex_schedule);
        }
        pthread_mutex_unlock(&coder->data->mutex_env->mutex_schedule);
        if (lock_mutex_dongles(first, second) == 0)
        {
            // set_available(first, 0);
            // set_available(second, 0);
            first->available = 0;
            second->available = 0;
            unlock_mutex_dongles(second, first);
            break;
        }
    }
    // while (!f(coder->id, first, second))
    //     pthread_cond_wait(&coder->data->cond_entry, &coder->data->mutex_env->mutex_schedule);
    // pthread_mutex_unlock(&coder->data->mutex_env->mutex_schedule);
    // set_available(&first, 0);
    // set_available(&second, 0);
    // lock_mutex_dongles(first, second);
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
    set_end_cooldown(first,get_timestamp() - coder->data->timestamp_start + coder->data->args->t_cooldown);
    set_end_cooldown(second,get_timestamp() - coder->data->timestamp_start + coder->data->args->t_cooldown);
    incr_compile_done(coder);
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

t_dongle   *get_dongle(t_coder *coder, int i)
{
    t_dongle *left = &coder->data->dongles[coder->id];
    t_dongle *right = &coder->data->dongles[(coder->id + 1) % coder->data->args->n_coders];

    t_dongle *first;
    t_dongle *second;
    if (left->id < right->id)
    {
        first = left;
        second = right;
    }
    else
    {
        first = right;
        second = left;
    }
    if (i == 0)
        return (first);
    else
        return (second);
}
void    *routine_coder(void *arg)
{
    t_coder *coder = (t_coder *)arg;
    t_dongle    *first;
    t_dongle    *second;

    first = get_dongle(coder, 0);
    second = get_dongle(coder, 1);
    pthread_mutex_lock(&coder->data->mutex_env->mutex_state_sim);
    while (!coder->data->start_sim)
        {
            pthread_cond_wait(&coder->data->cond_start, &coder->data->mutex_env->mutex_state_sim);
        }
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

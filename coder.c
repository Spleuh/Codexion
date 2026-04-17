/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsam <jsam@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 05:46:45 by jsam              #+#    #+#             */
/*   Updated: 2026/04/14 05:46:49 by jsam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void    incr_compile_done(t_coder *coder)
{
    if (get_stop_sim(coder->data))
        return ;
    pthread_mutex_lock(&coder->mutex_coder);
    coder->compiles_done += 1;
    pthread_mutex_unlock(&coder->mutex_coder);
}

int     get_compile_done(t_coder *coder)
{
    int result;

    if (get_stop_sim(coder->data))
        return (1);
    pthread_mutex_lock(&coder->mutex_coder);
    result = coder->compiles_done;
    pthread_mutex_unlock(&coder->mutex_coder);
    return (result);
}

void    set_last_compile(t_coder *coder, long timestamp)
{
    if (get_stop_sim(coder->data))
        return ;
    pthread_mutex_lock(&coder->mutex_coder);
    coder->last_compile_start = timestamp;
    pthread_mutex_unlock(&coder->mutex_coder);
}

long    get_last_comp_start(t_coder *coder)
{
    int result;

    pthread_mutex_lock(&coder->mutex_coder);
    result = coder->last_compile_start;
    pthread_mutex_unlock(&coder->mutex_coder);
    return (result);
}


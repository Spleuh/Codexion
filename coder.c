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


void    free_coders(t_coder *coders, int i)
{
    while (i >= 0)
    {
        i--;
        pthread_mutex_destroy(&coders[i].mutex_coder);
    }
    free(coders);
}

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

t_coder *init_coders(t_data *data)
{
    int i;
    t_coder *coders;

    coders = malloc(sizeof(t_coder) * (data->args->n_coders));
    if (!coders)
        return (NULL);
    i = 0;
    while (i < data->args->n_coders)
    {
        coders[i].id = i;
        coders[i].data = data;
        coders[i].last_compile_start = 0;
        coders[i].compiles_done = 0;
        if (pthread_mutex_init(&coders[i].mutex_coder, NULL) != 0)
            break;
        i++;
    }
    if (i < data->args->n_coders)
    {
        free_coders(coders, i);
        return (NULL);
    }
    return (coders);
}

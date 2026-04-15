/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsam <jsam@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 05:48:06 by jsam              #+#    #+#             */
/*   Updated: 2026/04/14 05:48:07 by jsam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void    join_thread_coders(t_coder *coders, int n)
{
    int i;
    
    i = 0;
    while (i < n)
    {
        pthread_join(coders[i].thread_coder, NULL);
        i++;
    }
}

void    rollback_thread_coders(t_coder *coders, int i)
{
    while (i >= 0)
    {
        i--;
        cancel_sim(coders->data);
        start_sim(coders->data);
    }
}
int    create_thread_coders(t_coder *coders)
{
    int i;
    int n;

    n = coders[0].data->args->n_coders;
    i = 0;
    while (i < n)
    {
        if (pthread_create(&coders[i].thread_coder, NULL, routine_coder, &coders[i]) != 0)
        {
            rollback_thread_coders(coders, i);
            return (1);
        }
        i++;
    }
    return (0);
}

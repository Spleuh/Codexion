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

void    rollback_thread_coders(t_data *data, int i)
{
    while (i >= 0)
    {
        i--;
        cancel_sim(data);
        start_sim(data);
        join_thread_coders(data->coders);
    }
}
int    create_thread_coders(t_data *data)
{
    int i;
    int n;

    n = coders[0].data->n_coders;
    i = 0;
    while (i < n)
    {
        if (pthread_create(&data->coders[i].thread_coder, NULL, routine_coder, &data->coders[i]) != 0)
        {
            rollback_thread_coders(data, i);
            return (1);
        }
        i++;
    }
    return (0);
}

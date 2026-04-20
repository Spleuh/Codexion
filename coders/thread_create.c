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



int    create_thread_coders(t_data *data)
{
    int i;

    i = 0;
    while (i < data->n_coders)
    {
        if (pthread_create(&data->coders[i].thread_coder, NULL, routine_coder, &data->coders[i]) != 0)
        {
            set_cancel_sim(data, 1);
            set_start_sim(data, 1);
            join_thread_coders(data, i);
            cleanup_data(data);
            return (1);
        }
        i++;
    }
    return (0);
}

int create_thread_all(t_data *data)
{
	if (create_thread_coders(data) != 0)
        return (1);
	if (pthread_create(&data->thread_monitor, NULL, routine_monitor, data) != 0)
    {
        set_cancel_sim(data, 1);
        set_start_sim(data, 1);
        join_thread_coders(data, data->n_coders);
        cleanup_data(data);
        return (1);
    } 
    return (0);
}



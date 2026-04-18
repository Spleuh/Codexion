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

void    join_thread_coders(t_data *data, int n)
{
    int i;
    
    i = 0;
    while (i < n)
    {
        pthread_join(data->coders[i].thread_coder, NULL);
        i++;
    }
}

int    create_thread_coders(t_data *data)
{
    int i;

    i = 0;
    while (i < data->n_coders)
    {
        if (pthread_create(&data->coders[i].thread_coder, NULL, routine_coder, &data->coders[i]) != 0)
        {
            cancel_sim(data);
            start_sim(data);
            join_thread_coders(data, i);
            free_data(data);
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
        join_thread_coders(data, data->n_coders);
        free_data(data);
        return (1);
    } 
    return (0);
}

void	join_thread_all(t_data *data)
{
	join_thread_coders(data, data->n_coders);
	pthread_join(data->thread_monitor, NULL);
}

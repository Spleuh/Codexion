/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsam <jsam@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 21:49:20 by jsam              #+#    #+#             */
/*   Updated: 2026/04/13 21:49:24 by jsam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "codexion.h"
void    destroy_cond_data(t_data *data)
{
    pthread_cond_destroy(&data->cond_entry);
    pthread_cond_destroy(&data->cond_start);
    return ;
}
int     init_cond_data(t_data *data)
{
    if (pthread_cond_init(&data->cond_entry, NULL) != 0)
        return (1);
    if (pthread_cond_init(&data->cond_start, NULL) != 0)
    {
        pthread_cond_destroy(&data->cond_entry);
        return (1);
    }
    return (0);
}



void    free_data(t_data *data)
{
    pthread_mutex_destroy(&data->mutex_data);
    destroy_cond_data(data);
    destroy_mutex_dongles(data->args->n_coders, data->dongles);
    free(data->dongles);
    free_coders(data->coders, data->args->n_coders);
    free_args(data->args);
    free(data);
}
t_data  *init_data(char **argv)
{
    t_data  *data;
    
    data = malloc(sizeof(t_data));
    if (!data)
        return (NULL);
    if (init_cond_data(data))
    {
        free(data);
        return (NULL);
    }
    if (pthread_mutex_init(&data->mutex_data, NULL) != 0)
    {
        destroy_cond_data(data);
        free(data);
        return (NULL);
    }
    data->args = init_args(argv);
    if (!data->args)
    {
        pthread_mutex_destroy(&data->mutex_data);
        destroy_cond_data(data);
        free(data);
        return (NULL);
    }
    data->dongles = init_dongles(data->args);
    if (!data->dongles)
    {
        free_args(data->args);
        pthread_mutex_destroy(&data->mutex_data);
        destroy_cond_data(data);
        free(data);
        return (NULL);
    }
    data->coders = init_coders(data);
    {
        destroy_mutex_dongles(data->args->n_coders, data->dongles);
        free(data->dongles);
        free_args(data->args);
        pthread_mutex_destroy(&data->mutex_data);
        destroy_cond_data(data);
        free(data);
        return (NULL);
    }
    // data->mutex_env = init_mutex_env();
    // if (!data->mutex_env)
    // {
    //     free_coders(data->coders);
    //     destroy_mutex_dongles(data->dongles);
    //     free(data->dongles);
    //     free_args(data->args);
    //     pthread_mutex_destroy(&data->mutex_data);
    //     destroy_cond_data(data);
    //     free(data);
    //     return (NULL);
    // }
    data->stop_sim = 0;
    data->start_sim = 0;
    data->cancel_sim = 0;
    return (data);
}
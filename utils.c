/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsam <jsam@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 05:48:16 by jsam              #+#    #+#             */
/*   Updated: 2026/04/14 05:48:17 by jsam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

char    *ft_strcpy(char *str)
{
    char    *result;
    int     i;
    int     len;

    len = strlen(str);
    result = malloc(sizeof(char) * (len + 1));
    if (!result)
        return (NULL);
    i = 0;
    while (i < len)
    {
        result[i] = str[i];
        i++;
    }
    result[i] = '\0';
    return (result);
}

long    get_timestamp()
{
    struct  timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000L + time.tv_usec / 1000L);
}

int     get_cancel_sim(t_data *data)
{
    int result;

    pthread_mutex_lock(&data->mutex_env->mutex_state_sim);
    result = data->cancel_sim;
    pthread_mutex_unlock(&data->mutex_env->mutex_state_sim);
    return (result);
}
void    cancel_sim(t_data *data)
{
    pthread_mutex_lock(&data->mutex_env->mutex_state_sim);
    data->cancel_sim = 1;
    pthread_mutex_unlock(&data->mutex_env->mutex_state_sim);
}
void    start_sim(t_data *data)
{
    pthread_mutex_lock(&data->mutex_env->mutex_state_sim);
    data->start_sim = 1;
    pthread_mutex_unlock(&data->mutex_env->mutex_state_sim);
    pthread_cond_broadcast(&data->cond_start);
}

void    print_debug(char *i)
{
    printf("%s\n", i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsam <jsam@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 05:47:58 by jsam              #+#    #+#             */
/*   Updated: 2026/04/14 05:48:00 by jsam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_scheduler *init_scheduler(t_data *data)
{
    t_scheduler *scheduler;

    scheduler = malloc(sizeof(t_scheduler));
    if (!scheduler)
        return (NULL);
    scheduler->dongles = data->dongles;
    scheduler->data = data;
    return (scheduler);
}

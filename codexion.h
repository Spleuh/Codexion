/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsam <jsam@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 10:41:39 by jsam              #+#    #+#             */
/*   Updated: 2026/03/29 10:41:42 by jsam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>

typedef struct mutex_dongle
{
	t_thread_coder	*left;
	t_thread_coder	*right;
	pthread_mutex_t	mutex;
}	t_mutex_dongle;

typedef struct thread_coder
{
	t_mutex_dongle	*left;
	t_mutex_dongle	*right;
}	t_thread_coder;
#endif
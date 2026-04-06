/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsam <jsam@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 10:41:39 by jsam              #+#    #+#             */
/*   Updated: 2026/04/06 01:02:29 by jsam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>

typedef struct s_data
{
	int	n_coders;
	int	t_burnout;
	int	t_compile;
	int	t_debug;
	int	t_refactor;
	int	n_compiles;
	int	t_cooldown;
	char	*scheduler;
}	t_data;

typedef struct s_coder
{
	int	id;
	pthread_t	thread;
	int	last_compile_start;

}	t_coder;

typedef struct s_dongle
{
	int	id;
	pthread_mutex mutex;
	t_coder	coder_left;
	t_coder	coder_right;
}	t_dongle;
#endif

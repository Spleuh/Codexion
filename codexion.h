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
# include <stdlib.h>
# include <string.h>

typedef struct s_req // struct request
{
	int		coder_id; // request from coder id
	long	deadline; // last compile + t_burnout
	long	order;  // security if same deadline
}	t_req;

typedef struct s_heap
{
	t_req	*arr; // array with all request
	int		size; // actual size of arr;
	int		max_capacity; // capacity 2 by default, only 2 coders for 1 dongle 
}	t_heap;

typedef struct s_dongle
{
	int				id; // dongle's id
	pthread_mutex_t	mutex; //mutex dongle
	pthread_cond_t	cond; // pthread cond for signal/broadcast
	long			end_cooldown; // end of cooldown
	int				available; // status available or not 
	t_heap			heap; //waiting heap fifo edf 
}	t_dongle;

typedef struct s_coder
{
	int			id; // coder's id
	pthread_t	thread; // thread
	long		last_compile_start; // last time the coder compile
	int			compiles_done; // number of compile done
	struct s_data	*data; // access to struct data
}	t_coder;

typedef struct s_data
{
	int				n_coders;
	int				t_burnout;
	int				t_compile;
	int				t_debug;
	int				t_refactor;
	int				n_compiles;
	int				t_cooldown;
	char			*scheduler;      // 'fifo' 'edf'
	pthread_mutex_t	mutex_print;      // mutex print log
	pthread_mutex_t	mutex_stop;       // mutex stop sim
	pthread_mutex_t mutex_start;	// mutex start sim
	int				stop_sim;		// 0 continue 1 stop
	int				start_sim;		// 0 wait 1 start
	t_dongle		*dongles;         // arr dongles
}	t_data;

// utils.c
char	*ft_strcpy(char *str);

// parser.c
t_data	*store_data(int argc, char **argv);
#endif

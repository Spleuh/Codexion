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
# include <stdlib.h> //atoi
# include <string.h> // strcmp
# include <stdio.h> // printf
// # include <unistd.h>
// # include <sys/time.h>

typedef struct s_data t_data;

typedef struct	s_node
{
	int		id_coder;
	long	ts_req;
}	t_node;

typedef	struct s_heap
{
	t_node	*tree;
	int		size;
	int		max_size;
}	t_heap;

typedef	struct	s_dongle
{
	int				id; // dongle's id

	t_heap			*queue; // priority queue

	pthread_mutex_t	mutex_dongle; //mutex dongle
	pthread_mutex_t	*mutex_state_dongles;

	pthread_cond_t	*cond_state_dongles;

	long			end_cooldown;
}	t_dongle;

typedef struct s_coder
{

	int				id; // coder's id
	int				compiles_done; // number of compile done

	long			last_compile_start; // last time the coder compile

	pthread_mutex_t	mutex_coder;
	pthread_t		thread_coder; // thread

	struct s_dongle	*first;  // lowest id dongle 
	struct s_dongle	*second; // highest id dongle
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
	int				scheduler;      // 0 'fifo' 1 'edf'

	pthread_mutex_t	mutex_print; // print mutex
	pthread_mutex_t	mutex_state_sim; // start stop cancel count_ready
	pthread_mutex_t	mutex_state_dongles;
	  

	pthread_cond_t	cond_start;
	pthread_cond_t	cond_state_dongles;

	long			ts_start; // timestamp start si when cond start ok
	
	int				start_sim;		// 0 wait 1 start
	int				stop_sim;		// 0 continue 1 stop
	int				cancel_sim;
	int				count_ready;	// while count < n_coders + 1 (monitor) wait

	t_dongle		*dongles;         // arr dongles
	t_coder			*coders;

	pthread_t		thread_monitor;
}	t_data;


#endif

// parser.c
int parser(int argc, char **argv);

// data_init.c
t_data  *init_data(char **argv);

// data_cleanup.c
void    cleanup_data(t_data *data);
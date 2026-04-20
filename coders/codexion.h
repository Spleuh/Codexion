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
# include <unistd.h> // usleep
# include <sys/time.h> //timestamp

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
	int				available; // dongle used 0 or free 1	

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
	pthread_mutex_t	mutex_ts_start; 

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

// utils.c
void	wait_ready_start(t_data *data);
void    print_mutex(t_data *data, char *str, int id);
void    print_stop_burned_out(t_data *data, int id);
void    print_debug(char *i);

// heap.c
void    heap_pop(t_heap *heap);
void    heap_insert(t_heap *heap, t_node node);

// heap_utils.c
void    add_requests(t_coder *coder);
void    remove_requests(t_coder *coder);
int     get_id_priority(t_heap *heap);

// data_init.c
t_data  *init_data(char **argv);

// data_cleanup.c
void    cleanup_data(t_data *data);
void    destroy_mutex_cond_data(t_data *data);
void    cleanup_dongles_coders(t_data *data);

// data_utils.c
void    set_cancel_sim(t_data *data, int i);
void    set_start_sim(t_data *data, int i);
long    get_timestamp(t_data *data);
int     get_cancel_sim(t_data *data);
int     get_count_ready(t_data *data);

// data_utils2.c
int     get_stop_sim(t_data *data);
void    set_stop_sim(t_data *data, int i);
void    incr_count_ready(t_data *data);
void    decr_count_ready(t_data *data);

// dongles_init.c
int     init_dongles(t_data *data);

// dongles_cleanup.c
void    cleanup_dongles(t_data *data);
void    free_queue_dongles(int  n, t_dongle *dongles);
void    destroy_mutex_dongles(int i, t_dongle *dongles);

// dongles_utils.c
// long    get_end_cooldown(t_dongle *dongle);
void    set_available(t_data *data, t_dongle *dongle, int i);

// coders_init.c
int     init_coders(t_data *data);

// coders_cleanup.c
void    cleanup_coders(t_data *data);
void    destroy_mutex_coders(t_coder *coders, int n);

// coders_utils.c
void	set_last_compile(t_coder *coder, long timestamp);
void    incr_compile_done(t_coder *coder);
int     get_compile_done(t_coder *coder);
long    get_last_comp_start(t_coder *coder);

// thread_create.c
int create_thread_all(t_data *data);

// thread_join.c
void	join_thread_all(t_data *data);
void    join_thread_coders(t_data *data, int n);

// coders_routine.c
void    *routine_coder(void *arg);

// coders_routine_utils.c
int     check_priority(t_coder *coder);
int     update_cd_dongles(t_coder *coder);
int     try_lock_dongles(t_coder *coder);
void    unlock_dongles(t_coder *coder);

// monitor_routine.c
void    *routine_monitor(void *arg);
void    send_broadcast_state_dongle(t_data *data);
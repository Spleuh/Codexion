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
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data t_data;


typedef	struct	t_dongle
{
	pthread_mutex_t	mutex_dongle; //mutex dongle
	int				id; // dongle's id
	int				available;
	int				id_priority;
	long			end_cooldown;
}	t_dongle;

typedef struct s_coder
{
	pthread_t		thread_coder; // thread
	pthread_mutex_t	mutex_coder;
	int				id; // coder's id
	int				compiles_done; // number of compile done
	long			last_compile_start; // last time the coder compile
	struct s_data	*data; // access to struct data
}	t_coder;

typedef	struct	s_monitor
{
	pthread_t		thread_monitor;
	t_coder			*coders;
	t_data			*data;
}	t_monitor;

typedef struct	s_scheduler
{
	pthread_t	thread_scheduler;
	t_dongle	*dongles;
	t_data		*data;
}	t_scheduler;

typedef struct s_mutex_env
{
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_schedule;
	pthread_mutex_t	mutex_state_sim;

}	t_mutex_env;

typedef struct	s_args
{
	int				n_coders;
	int				t_burnout;
	int				t_compile;
	int				t_debug;
	int				t_refactor;
	int				n_compiles;
	int				t_cooldown;
	char			*schedule;      // 'fifo' 'edf'
}	t_args;

typedef struct s_data
{

	t_mutex_env			*mutex_env;
	long			timestamp_start;
	pthread_cond_t	cond_entry;		// check condition priority EDF;
	pthread_cond_t	cond_start;
	int				stop_sim;		// 0 continue 1 stop
	int				start_sim;		// 0 wait 1 start
	int				cancel_sim;
	t_dongle		*dongles;         // arr dongles
	t_coder			*coders;
	t_args			*args;
}	t_data;

// utils.c
char    *ft_strcpy(char *str);
void    cancel_sim(t_data *data);
void    start_sim(t_data *data);
int     get_cancel_sim(t_data *data);
long    get_timestamp();
void    print_debug(int i);

// parser.c
int parser(int argc, char **argv);

// data.c
t_data  *init_data(char **argv);
void    free_data(t_data *data);
void    set_start_sim(t_data *data, int i);

// scheduler.c 
t_scheduler *init_scheduler(t_data *data);

// monitor.c 
t_monitor   *init_monitor(t_data *data);
int         get_stop_sim(t_data *data);
void    create_thread_monitor(t_monitor *monitor);
void    set_stop_sim(t_data *data, int i);

// dongle.c
void    destroy_mutex_dongles(int i, t_dongle *dongles);
t_dongle    *init_dongles(t_args *args);
void    set_available(t_dongle **dongle, int i);
int     check_available(int	id_coder, t_dongle *first, t_dongle *second);
int     check_id_priority(int id_coder, t_dongle *first, t_dongle *second);
int     init_mutex_dongles(t_dongle *dongles, int n);
void    set_end_cooldown(t_dongle *dongle, long timestamp);
long    get_end_cooldown(t_dongle *dongle);
int     get_available(t_dongle *dongle);

// coder.c
void    free_coders(t_coder *coders, int i);
t_coder *init_coders(t_data *data);
void    set_last_compile(t_coder *coder, long timestamp);
void    incr_compile_done(t_coder *coder);
int     get_compile_done(t_coder *coder);

// args.c
void    free_args(t_args *args);
t_args  *init_args(char **argv);

// thread.c
int    create_thread_coders(t_coder *coders);
void    join_thread_coders(t_coder *coders, int n);

// routine_coder.c
void    *routine_coder(void *arg);

// routine_monitor.c
void    *routine_monitor(void *arg);

// routine_scheduler.c
void    *routine_scheduler(void *arg);

// print.c
void    print_mutex(t_data *data, char *str, int id);

// mutex_env.c
void    destroy_mutex_mutex_env(t_mutex_env *mutex_env);
t_mutex_env *init_mutex_env();
#endif

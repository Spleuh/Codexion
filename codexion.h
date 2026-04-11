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



typedef struct s_dongle
{
	int				id; // dongle's id
	int				id_priority; //coder's id
    int				n_dongles;
	long			lst_cmp_0;
	long			lst_cmp_1;
	pthread_mutex_t	mutex; //mutex dongle
	pthread_mutex_t	mutex_lst_cmp; //mutex dongle
	pthread_mutex_t	mutex_available; //mutex dongle
	pthread_mutex_t	mutex_id_priority; //mutex dongle
	long			end_cooldown; // end of cooldown
	int				available; // status available or not 
}	t_dongle;

typedef struct s_coder
{
	int			id; // coder's id
	pthread_t	thread; // thread
	long		last_compile_start; // last time the coder compile
	pthread_mutex_t	mutex_compiles_done;
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
	long			timestamp_start;
	pthread_mutex_t	mutex_print;      // mutex print log
	pthread_mutex_t	mutex_stop;       // mutex stop sim
	pthread_mutex_t mutex_start;	// mutex start sim
	pthread_mutex_t mutex_entry;	// global mutex
	pthread_cond_t	cond_entry;		// check condition priority EDF;
	pthread_cond_t	cond_start;
	pthread_t		monitor;
	pthread_t		thread_planner;
	int				stop_sim;		// 0 continue 1 stop
	int				start_sim;		// 0 wait 1 start
	t_dongle		*dongles;         // arr dongles
}	t_data;

// utils.c
char	*ft_strcpy(char *str);
void    print(t_data *data, char *str);
long    get_timestamp();
char    *ft_ltoa(long l);
char	*ft_strjoin(char *s1, char *s2);
void	print_test();

// parser.c
t_data	*store_data(int argc, char **argv);

// coder.c
int    init_coders(t_coder *coders, t_data *data);
long    get_deadline(t_coder *coder);
int     check_available(int coder_id, t_dongle *first, t_dongle *second);

// dongle.c
int init_dongles(t_data *data);
void    free_dongles(t_dongle *dongles, int n_dongles);

// monitor.c
int init_monitor(t_coder *coder);

// scheduler.c
int condition_fifo(t_dongle *first, t_dongle *second);
int init_scheduler(t_data *data);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsam <jsam@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 10:20:52 by jsam              #+#    #+#             */
/*   Updated: 2026/03/31 15:29:15 by jsam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "codexion.h"
#include <unistd.h>

void	*thread_cycle(void *arg)
{
	t_mutex_dongle	*md;

	md = (t_mutex_dongle *) arg;
	pthread_mutex_lock(&md->mutex);
	sleep(1);
	pthread_mutex_unlock(&md->mutex);
	pthread_exit(NULL);
}

pthread_t	*init_chain()
{
	int			i;
	void	*result;

	i = 7;

	while (i)
	{
		if (i % 2)
		{
			t_mutex_dongle dongle;

			dongle.left = &result;
			result.right = &dongle;
			result = &dongle;
		}
		else
		{
			t_thread_coder coder;

			coder.left = &result;
			result.right = &coder;
			result = &coder;
		}

	}
}

void	add_nodes(void *list, int i)
{
	t_mutex_dongle	dongle;
	t_thread_coder	coder;
	void			**tmp;

	coder->right = &dongle;
	dongle->left = &coder;
	*tmp = list;
	while (tmp->right)
		*tmp = tmp->next;
	(*tmp)->right = &coder;
	coder->left = *tmp
}

int	main(void)
{
	t_mutex_dongle	md;
	pthread_t	coder;
	int	err;

	md.data = 0;
	if (pthread_mutex_init(&md.mutex, NULL) != 0)
	{
		printf("fail init mutex\n");
		return (1);
	}
	err = pthread_create(&coder, NULL, thread_cycle, &md);
	if (err != 0)
	{
		printf("Create thread fail");
		return (1);
	}
	pthread_join(coder, NULL);
	pthread_mutex_destroy(&md.mutex);


	return (0);
}

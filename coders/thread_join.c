#include "codexion.h"

void    join_thread_coders(t_data *data, int n)
{
    int i;
    
    i = 0;
    while (i < n)
    {
        pthread_join(data->coders[i].thread_coder, NULL);
        i++;
    }
}

void	join_thread_all(t_data *data)
{
	join_thread_coders(data, data->n_coders);
	pthread_join(data->thread_monitor, NULL);
}
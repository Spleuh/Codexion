#include "codexion.h"

void    rollback_thread()
{
    
}

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
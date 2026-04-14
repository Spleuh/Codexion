#include "codexion.h"

void    join_thread_coders(t_coder *coders, int n)
{
    int i;
    
    i = 0;
    while (i < n)
    {
        pthread_join(coders[i].thread_coder, NULL);
        i++;
    }
}

void    rollback_thread_coders(t_coder *coders, int i)
{
    while (i >= 0)
    {
        i--;
        cancel_sim(coders->data);
        start_sim(coders->data);
    }
}
void    create_thread_coders(t_coder *coders)
{
    int i;

    i = 0;
    while (i < coders->data->args->n_coders)
    {
        if (pthread_create(&coders[i].thread_coder, NULL, routine_coder, coders[i]) != 0)
        {
            rollback_thread_coders(coders, i);
            return ;
        }
        i++;
    }
}
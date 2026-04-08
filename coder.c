#include "codexion.h"

void    init_coders(t_coder *coders, int n_coders)
{
    int i;
    int tmp;

    if (!coders)
        return ;
    i = 0;
    tmp = 0;
    while (tmp == 0 && i < n_coders)
    {
        coders[i].id = i;
        tmp = pthread_create(&coders[i].thread, NULL, routine, coders[i]);
        i++;
    }
    if (tmp != 0)
    {
        i--;
        while(i > 0)
        {
            pthread_join(&coders[i], NULL);
            i--;
        }
        return ;
    }
}

void    routine(t_coder *coder)
{
    pthread_mutex_lock(&coder->data->start_mutex);
    while (!data->start_sim)
        pthread_cond_wait(&coder->data->start_cond, &data->start_mutex);
    pthread_mutex_unlock(&coder->data->start_mutex);

}
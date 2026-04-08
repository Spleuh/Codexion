#include "codexion.h"
#include <sys/time.h>


long    get_timestamp()
{
    struct  timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000L + time.tv_usec / 1000L);
}

void    take_dongles(t_coder *coder)
{
    t_dongle *left = &coder->data->dongles[coder->id];
    t_dongle *right = &coder->data->dongles[(coder->id + 1) % coder->data->n_coders];

    t_dongle *first = left->id < right->id ? left : right;
    t_dongle *second = left->id < right->id ? right : left;
    pthread_mutex_lock(&first->mutex);
    pthread_mutex_lock(&second->mutex);
    printf("%d has taken dongle %d\n", coder->id, left->id);
    printf("%d has taken dongle %d\n", coder->id, right->id);
}

void    release_dongles(t_coder *coder)
{
    t_dongle *left = &coder->data->dongles[coder->id];
    t_dongle *right = &coder->data->dongles[(coder->id + 1) % coder->data->n_coders];
    pthread_mutex_unlock(&left->mutex);
    pthread_mutex_unlock(&right->mutex);
}

void    debug(t_coder *coder)
{
    printf("%ld %d is debugging\n", get_timestamp(), coder->id);
    usleep(coder->data->t_debug * 1000);
}

void    refactor(t_coder *coder)
{
    printf("%ld %d is refactoring\n", get_timestamp(), coder->id);
    usleep(coder->data->t_refactor * 1000);
}



void   compile(t_coder *coder)
{
    coder->last_compile_start = get_timestamp();
    usleep(coder->data->t_compile * 1000);
    coder->last_compile_start = get_timestamp();
    coder->compiles_done++;
}

void    *routine(void *arg)
{
    t_coder *coder = (t_coder *)arg;
    pthread_mutex_lock(&coder->data->mutex_start);
    while (!coder->data->start_sim)
        pthread_cond_wait(&coder->data->cond_start, &coder->data->mutex_start);
    pthread_mutex_unlock(&coder->data->mutex_start);
    while (!coder->data->stop_sim)
    {
        take_dongles(coder);
        compile(coder);
        release_dongles(coder);
        debug(coder);
        refactor(coder);
    }
    return (NULL);
}

int    init_coders(t_coder *coders, t_data *data)
{
    int i;
    int tmp;

    if (!coders)
        return (1);
    i = 0;
    tmp = 0;
    while (tmp == 0 && i < data->n_coders)
    {
        coders[i].id = i;
        coders[i].data = data;
        coders[i].last_compile_start = 0;
        coders[i].compiles_done = 0;
        tmp = pthread_create(&coders[i].thread, NULL, routine, &coders[i]);
        i++;
    }
    if (tmp != 0)
    {
        i--;
        pthread_mutex_lock(&data->mutex_start);
        data->start_sim = 1;
        pthread_mutex_unlock(&data->mutex_start);
        pthread_cond_broadcast(&data->cond_start);
        while(i >= 0)
        {
            pthread_join(coders[i].thread, NULL);
            i--;
        }
        return (1);
    }
    return (0);
}
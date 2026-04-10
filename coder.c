#include "codexion.h"




long    get_deadline(t_coder *coder)
{
    long    result;

    result = coder->last_compile_start + coder->data->t_burnout;
    return result;
}

int     check_available(int coder_id, t_dongle *first, t_dongle *second)
{
    if (!first->available || !second->available)
        return (0);
    if ((first->id_priority == -1 || first->id_priority == coder_id) && (second->id_priority == -1 || second->id_priority == coder_id))
        return (1);
    return (0);
}
void    take_dongles(t_coder *coder, t_dongle *first, t_dongle *second)
{


    while (!check_available(coder->id, first, second))
    {
        pthread_cond_wait(&coder->data->cond_entry, &coder->data->mutex_entry);
    }
    pthread_mutex_lock(&first->mutex);
    pthread_mutex_lock(&second->mutex);
    first->available = 0;
    second->available = 0;
    printf("%d has taken dongle %d\n", coder->id, first->id);
    printf("%d has taken dongle %d\n", coder->id, second->id);
}

void    release_dongles(t_coder *coder, t_dongle **first, t_dongle **second)
{
    (*first)->available = 1;
    (*second)->available = 1;
    pthread_mutex_unlock(&(*first)->mutex);
    pthread_mutex_unlock(&(*second)->mutex);
    pthread_cond_broadcast(&coder->data->cond_entry);
}

void    debug(t_coder *coder)
{
    char    *timestamp;
    char    *id_coder;
    char    *str;

    id_coder = ft_ltoa((long)coder->id);
    if (!id_coder)
        return ;
    timestamp = ft_ltoa((get_timestamp() - coder->data->timestamp_start));
    if (!timestamp)
        return ;
    str = ft_strjoin(timestamp, " ");
    if (!str)
        return ;
    str = ft_strjoin(str, id_coder);
    if (!str)
        return ;
    str = ft_strjoin(str, " is debugging");
    if (!str)
        return ;
    print(coder->data, str);
    usleep(coder->data->t_debug * 1000);
}

void    refactor(t_coder *coder)
{
    printf("%ld %d is refactoring\n", get_timestamp(), coder->id);
    usleep(coder->data->t_refactor * 1000);
}



void   compile(t_coder *coder)
{
    t_dongle *left = &coder->data->dongles[coder->id];
    t_dongle *right = &coder->data->dongles[(coder->id + 1) % coder->data->n_coders];

    t_dongle *first = left->id < right->id ? left : right;
    t_dongle *second = left->id < right->id ? right : left;

    pthread_mutex_lock(&coder->data->mutex_entry);
    take_dongles(coder, first, second);
    pthread_mutex_unlock(&coder->data->mutex_entry);

    coder->last_compile_start = get_timestamp();
    usleep(coder->data->t_compile * 1000);
    coder->compiles_done++;

    release_dongles(coder, &first, &second);
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
        compile(coder);
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
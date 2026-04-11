#include "codexion.h"

long    get_deadline(t_coder *coder)
{
    long    result;

    result = coder->last_compile_start + coder->data->t_burnout;
    return result;
}

int     check_available(int coder_id, t_dongle *first, t_dongle *second)
{
    int result;

    (void)coder_id;
    result = 1;
    pthread_mutex_lock(&first->mutex_available);
    pthread_mutex_lock(&second->mutex_available);

    if (!first->available || !second->available)
        result = 0;
    pthread_mutex_unlock(&first->mutex_available);
    pthread_mutex_unlock(&second->mutex_available);
    return (result);
}

int     edf(int coder_id, t_dongle *first, t_dongle *second)
{
    int result;

    result = check_available(coder_id, first, second);
    if (result == 0)
        return (result);
    pthread_mutex_lock(&first->mutex_id_priority);
    pthread_mutex_lock(&second->mutex_id_priority);
    if (first->id_priority != -1 && first->id_priority != coder_id && second->id_priority != -1 && second->id_priority != coder_id)
        result = 0;
    pthread_mutex_unlock(&first->mutex_id_priority);
    pthread_mutex_unlock(&second->mutex_id_priority);
    return (result);
}
void    take_dongles(t_coder *coder, t_dongle *first, t_dongle *second)
{
    long    timestamp;
    int (*f)(int, t_dongle*, t_dongle*);
    if (strcmp(coder->data->scheduler, "fifo") == 0)
        f = &check_available;
    else if (strcmp(coder->data->scheduler, "edf") == 0)
    {
        f = &edf;
    }
    
    while (!f(coder->id, first, second))
    {
        pthread_cond_wait(&coder->data->cond_entry, &coder->data->mutex_entry);
    }

    pthread_mutex_lock(&first->mutex);
    pthread_mutex_lock(&second->mutex);

    pthread_mutex_lock(&first->mutex_available);
    pthread_mutex_lock(&second->mutex_available);
    first->available = 0;
    second->available = 0;

    pthread_mutex_unlock(&first->mutex_available);
    pthread_mutex_unlock(&second->mutex_available);

    pthread_mutex_lock(&coder->data->mutex_print);
    timestamp = get_timestamp() - coder->data->timestamp_start;
    printf("%ld %d has taken dongle %d\n",timestamp, coder->id, first->id);
    printf("%ld %d has taken dongle %d\n",timestamp, coder->id, second->id);
    pthread_mutex_unlock(&coder->data->mutex_print);
}

void    release_dongles(t_coder *coder, t_dongle **first, t_dongle **second)
{
    pthread_mutex_lock(&(*first)->mutex_available);
    pthread_mutex_lock(&(*second)->mutex_available);
    (*first)->available = 1;
    (*second)->available = 1;
    pthread_mutex_unlock(&(*first)->mutex_available);
    pthread_mutex_unlock(&(*second)->mutex_available);

    pthread_mutex_unlock(&(*first)->mutex);
    pthread_mutex_unlock(&(*second)->mutex);
    pthread_cond_broadcast(&coder->data->cond_entry);
}

void    debug(t_coder *coder)
{


    long    timestamp;

    timestamp = get_timestamp() - coder->data->timestamp_start;
    pthread_mutex_lock(&coder->data->mutex_print);
    printf("%ld %d is debugging\n",timestamp, coder->id);
    pthread_mutex_unlock(&coder->data->mutex_print);
    usleep(coder->data->t_debug * 1000);
}

void    refactor(t_coder *coder)
{
    long    timestamp;

    pthread_mutex_lock(&coder->data->mutex_print);
    timestamp = get_timestamp() - coder->data->timestamp_start;
    printf("%ld %d is refactoring\n", timestamp, coder->id);
    pthread_mutex_unlock(&coder->data->mutex_print);
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
    coder->last_compile_start = get_timestamp() - coder->data->timestamp_start;
    pthread_mutex_lock(&first->mutex_lst_cmp);
    if (coder->id % 2)
        first->lst_cmp_1 = coder->last_compile_start;
    else
        first->lst_cmp_0 = coder->last_compile_start;
    if (coder->id % 2)
        second->lst_cmp_1 = coder->last_compile_start;
    else
        second->lst_cmp_0 = coder->last_compile_start;
    pthread_mutex_unlock(&first->mutex_lst_cmp);
    usleep(coder->data->t_compile * 1000);
    pthread_mutex_lock(&coder->mutex_compiles_done);
    coder->compiles_done++;
    pthread_mutex_unlock(&coder->mutex_compiles_done);

    release_dongles(coder, &first, &second);
    printf("first available: %d second available: %d\n", first->available, second->available);
}

void    *routine(void *arg)
{
    t_coder *coder = (t_coder *)arg;
    int     stop;

    pthread_mutex_lock(&coder->data->mutex_start);
    while (!coder->data->start_sim)
        pthread_cond_wait(&coder->data->cond_start, &coder->data->mutex_start);
    pthread_mutex_unlock(&coder->data->mutex_start);
    pthread_mutex_lock(&coder->data->mutex_stop);
    stop = coder->data->stop_sim;
    pthread_mutex_unlock(&coder->data->mutex_stop);
    while (!stop)
    {
        compile(coder);
        debug(coder);
        refactor(coder);
        pthread_mutex_lock(&coder->data->mutex_stop);
        stop = coder->data->stop_sim;
        pthread_mutex_unlock(&coder->data->mutex_stop);

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
        if (pthread_mutex_init(&coders[i].mutex_compiles_done, NULL) != 0)
            break;
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
		    pthread_mutex_destroy(&coders[i].mutex_compiles_done);
            pthread_join(coders[i].thread, NULL);
            i--;
        }
        return (1);
    }
    return (0);
}
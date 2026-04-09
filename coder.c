#include "codexion.h"
#include <sys/time.h>


long    get_timestamp()
{
    struct  timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000L + time.tv_usec / 1000L);
}

long    get_deadline(t_coder *coder)
{
    long    result;

    result = coder->last_compile_start + coder->data->t_burnout;
    return result;
}

int get_last_i(t_req *arr)
{
    int i;

    i = 0;
    while (arr[i].coder_id)
        i++;
    return i;
}
int     check_available(int coder_id, t_dongle *first, t_dongle *second)
{
    printf("first: %d second: %d\n", first->available, second->available);
    printf("first id: %d second id: %d \n",first->id_priority, second->id_priority);
    if (!first->available || !second->available)
        return (0);
    if ((first->id_priority == -1 || first->id_priority == coder_id) && (second->id_priority == -1 || second->id_priority == coder_id))
        return (1);
    return (0);
}
void    print_test(int i)
{
    printf("check_available: %d\n", i);
}
void    take_dongles(t_coder *coder, t_dongle *first, t_dongle *second)
{

    add_request(coder, first, second);

    pthread_mutex_lock(&coder->data->mutex_entry);
    int i;

    i = check_available(coder->id, first, second);
    while (!i)
    {
        print_test(i);
        pthread_cond_wait(&coder->data->cond_entry, &coder->data->mutex_entry);
        i = check_available(coder->id, first, second);
    }
    pthread_mutex_lock(&first->mutex);
    pthread_mutex_lock(&second->mutex);
    first->available = 0;
    second->available = 0;
    pthread_mutex_unlock(&coder->data->mutex_entry);
    printf("%d has taken dongle %d\n", coder->id, first->id);
    printf("%d has taken dongle %d\n", coder->id, second->id);
}

void    release_dongles(t_coder *coder, t_dongle *first, t_dongle *second)
{
    remove_req(coder, first);
    remove_req(coder, second);
    sort_edf(first->heap);
    sort_edf(second->heap);
    if (first->heap->arr)
        first->id_priority = first->heap->arr[0].coder_id;
    else
        first->id_priority = -1;
    if (second->heap->arr)
        second->id_priority = second->heap->arr[0].coder_id;
    else
        second->id_priority = -1;
    first->available = 1;
    second->available = 1;
    pthread_mutex_unlock(&first->mutex);
    pthread_mutex_unlock(&second->mutex);
    pthread_cond_broadcast(&coder->data->cond_entry);
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
    t_dongle *left = &coder->data->dongles[coder->id];
    t_dongle *right = &coder->data->dongles[(coder->id + 1) % coder->data->n_coders];

    t_dongle *first = left->id < right->id ? left : right;
    t_dongle *second = left->id < right->id ? right : left;
    take_dongles(coder, first, second);

    coder->last_compile_start = get_timestamp();
    usleep(coder->data->t_compile * 1000);
    coder->compiles_done++;

    release_dongles(coder, first, second);
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
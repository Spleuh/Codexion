#include "codexion.h"

void    free_heap(t_heap *heap)
{
    pthread_mutex_destroy(&heap->mutex_heap);
    free(heap->arr);
    free(heap);
    return ;
}

t_heap  *init_heap()
{
    t_heap  *heap;

    heap = malloc(sizeof(t_heap));
    if (!heap)
        return (NULL);
    heap->size = 0;
    heap->max_capacity = 2;
    heap->arr = init_req_arr(heap->max_capacity);
    if (!heap->arr)
    {
        free(heap);
        return (NULL);
    }
    if (pthread_mutex_init(&heap->mutex_heap, NULL) != 0)
    {
        free(heap->arr);
        free(heap);
        return (NULL);
    }
    return (heap);
}

int check_req(t_heap *heap, int id)
{
    int i;

    i = 0;
    while (i < heap->size)
    {
        if (heap->arr[i].coder_id == id)
            return (1);
        i++;
    }
    return (0);
}

int    add_request(t_coder *coder, t_dongle **first, t_dongle **second)
{
    t_req   req_first;
    t_req   req_second;

    pthread_mutex_lock(&(*first)->heap->mutex_heap);
    pthread_mutex_lock(&(*second)->heap->mutex_heap);
    req_first.coder_id = coder->id;
    req_first.deadline = get_deadline(coder);
    req_second.coder_id = coder->id;
    req_second.deadline = get_deadline(coder);
    (*first)->heap->arr[get_last_i((*first)->heap->arr)] = req_first;
    (*second)->heap->arr[get_last_i((*second)->heap->arr)] = req_second;
    pthread_mutex_unlock(&(*first)->heap->mutex_heap);
    pthread_mutex_unlock(&(*second)->heap->mutex_heap);
    return (0);
}

void    remove_req(t_coder *coder, t_dongle **dongle)
{
    int i;
    int j;
    t_req  *new_arr;

    new_arr = malloc(sizeof(t_req) * (*dongle)->heap->max_capacity);
    if (!new_arr)
        return ;
    pthread_mutex_lock(&(*dongle)->heap->mutex_heap);
    i = 0;
    j = 0;
    while (i < (*dongle)->heap->size)
    {
        if ((*dongle)->heap->arr[i].coder_id != coder->id)
            new_arr[j] = (*dongle)->heap->arr[i];
        else
            j--;
        j++;
        i++;
    }
    free((*dongle)->heap->arr);
    (*dongle)->heap->arr = new_arr;
    pthread_mutex_unlock(&(*dongle)->heap->mutex_heap);
    return ;
}

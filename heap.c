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

void    remove_req(t_heap *heap, int id)
{
    int i;
    int j;
    t_req  *new_arr;

    new_arr = malloc(sizeof(t_req) * heap->max_capacity);
    if (!new_arr)
        return ;
    i = 0;
    j = 0;
    while (i < heap->size)
    {
        if (heap->arr[i].coder_id != id)
            new_arr[j] = heap->arr[i];
        else
            j--;
        j++;
        i++;
    }
    free(heap->arr);
    heap->arr = new_arr;
    return ;
}

void    heap_add_req(t_heap *heap, t_req request)
{
    int i;

    i = 0;
    if (check_req(heap, request.coder_id))
        return ;
    while (i < heap->size)
        i++;
    heap->arr[i] = request;
    heap->size += 1;
    return ;
}
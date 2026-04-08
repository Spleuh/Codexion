#include "codexion.h"

t_heap  *init_heap()
{
    t_heap  *heap;

    heap = malloc(sizeof(t_heap));
    if (!heap)
        return ;
    heap->size = 0;
    heap->max_capacity = 2;
    heap->arr = init_req_arr(heap->max_capacity);
    if (!heap->arr)
    {
        free(heap);
        return ;
    }
    return (heap);
}
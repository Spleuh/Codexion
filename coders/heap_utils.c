#include "codexion.h"



int     get_id_priority(t_heap *heap)
{
    return (heap[0].id_coder);
}

void    add_requests(t_coder *coder)
{
    t_node  request;

    init_request(&request);
    pthread_mutex_lock(&coder->data->mutex_state_dongles);
    heap_insert(coder->first->heap, request);
    heap_insert(coder->second->heap, request);
    pthread_broadcast(&coder->data->cond_state_dongles);
    pthread_mutex_unlock(&coder->data->mutex_state_dongles);
}
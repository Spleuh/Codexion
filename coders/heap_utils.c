#include "codexion.h"

int     get_id_priority(t_heap *heap)
{
    return (heap->tree[0].id_coder);
}

void    init_request(t_coder *coder, t_node *request)
{
    request->id_coder = coder->id;
    if (coder->data->scheduler != 0)
        request->ts_req = get_last_comp_start(coder);
    else
        request->ts_req = get_timestamp(coder->data);
}

void    remove_requests(t_coder *coder)
{
    heap_pop(coder->first->queue);
    heap_pop(coder->second->queue);
}

void    add_requests(t_coder *coder)
{
    t_node  request;

    pthread_mutex_lock(&coder->data->mutex_state_dongles);
    init_request(coder, &request);
    heap_insert(coder->first->queue, request);
    heap_insert(coder->second->queue, request);
    pthread_cond_broadcast(&coder->data->cond_state_dongles);
    pthread_mutex_unlock(&coder->data->mutex_state_dongles);
}
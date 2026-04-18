#include "codexion.h"

int     check_priority(t_coder *coder)
{
    if (get_id_priority(coder->first->heap) != coder->id)
        return (1);
    if (get_id_priority(coder->second->heap) != coder->id)
        return (1);
    if (get_end_cooldown(coder->first) > get_timestamp(coder->data))
        return (1);
    if (get_end_cooldown(coder->second) > get_timestamp(coder->data))
        return (1);
    return (0);
}

int     check_dongles(t_coder *coder)
{
    if (check_id_priority(coder) != 0)
    {
    }
    heap_pop(first->heap);
    heap_pop(second->heap);
    pthread_mutex_unlock(&coder->second);
    pthread_mutex_unlock(&coder->first);
}
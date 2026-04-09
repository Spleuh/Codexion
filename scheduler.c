#include "codexion.h"



int    sort_edf(t_heap *heap)
{
    t_req   tmp;
    int     i;
    int     j;

    i = 0;
    while (i < heap->size)
    {
        j = i + 1;
        while (j < heap->size)
        {
            if (heap->arr[i].deadline > heap->arr[j].deadline)
            {
                tmp = heap->arr[j];
                heap->arr[j] = heap->arr[i];
                heap->arr[i] = tmp;
            }
            j++;
        }
        i++;
    }
    return (0);
}
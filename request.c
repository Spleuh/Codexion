#include "codexion.h"

t_req   *init_req_arr(int max_capacity)
{
    t_req   arr;

    arr = malloc(sizeof(t_req) * max_capacity)
    if (!arr)
        return (NULL);
    return arr;
}
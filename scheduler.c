#include "codexion.h"

int condition_fifo(t_dongle *first, t_dongle *second)
{
    if (first->available == 0 || second->available == 0)
        return (1);
    return (0);
}
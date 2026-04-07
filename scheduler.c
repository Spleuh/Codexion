#include "codexion.h"

void    edf_next_coder(t_dongle *dongle, t_coder *coders, t_data *data)
{
    long    deadline;
    int     id_coder;
    int     result;

    id_coder = dongle->id;
    result = id_coder;
    deadline = coders[id_coder]->last_compile + data->t_burnout;
    id_coder = (id_coder - 1 + data->n_coders) % data->n_coders;
    if (deadline > coder[id_coder]->last_compile + data->t_burnout)
        result = id_coder;
    elif (deadline == coder[id_coder]->last_compile + data->t_burnout)
        result = -1;
    dongle->reserved_for = result;
}
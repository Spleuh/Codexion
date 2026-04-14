#include "codexion.h"

t_scheduler *init_scheduler(t_data *data)
{
    t_scheduler *scheduler;

    scheduler = malloc(sizeof(t_scheduler));
    if (!scheduler)
        return (NULL);
    scheduler->dongles = data->dongles;
    scheduler->data = data;
    return (scheduler);
}
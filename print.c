#include "codexion.h"

void    print_mutex(t_data *data, char *str)
{
    if (get_stop_sim())
        return ;
    pthread_mutex_lock(&data->print_mutex);
    print
    pthread_mutex_unlock(&data->print_mutex);
}
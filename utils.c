#include "codexion.h"

char    *ft_strcpy(char *str)
{
    char    *result;
    int     i;
    int     len;

    len = strlen(str);
    result = malloc(sizeof(char) * (len + 1));
    if (!result)
        return (NULL);
    i = 0;
    while (i < len)
    {
        result[i] = str[i];
        i++;
    }
    result[i] = '\0';
    return (result);
}

long    get_timestamp()
{
    struct  timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000L + time.tv_usec / 1000L);
}

int     get_cancel_sim(t_data *data)
{
    int result;

    pthread_mutex_lock(data->mutex_data);
    result = data->cancel_sim;
    pthread_mutex_unlock(&data->mutex_data);
    return (result);
}
void    cancel_sim(t_data *data)
{
    pthread_mutex_lock(&data->mutex_data);
    data->cancel_sim = 1;
    pthread_mutex_unlock(&data->mutex_data);
}
void    start_sim(t_data *data)
{
    pthread_mutex_lock(&data->mutex_data);
    data->start_sim = 1;
    pthread_mutex_unlock(&data->mutex_data);
    pthread_cond_broadcast(&data->cond_start, &data->mutex_data);
}

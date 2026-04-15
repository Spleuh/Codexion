#include "codexion.h"

void    destroy_mutex_mutex_env(t_mutex_env *mutex_env)
{
    pthread_mutex_destroy(&mutex_env->mutex_print);
    pthread_mutex_destroy(&mutex_env->mutex_schedule);
    pthread_mutex_destroy(&mutex_env->mutex_state_sim);
}
t_mutex_env *init_mutex_env()
{
    t_mutex_env *mutex_env;

    mutex_env = malloc(sizeof(t_mutex_env));
    if (!mutex_env)
        return (NULL);
    if (pthread_mutex_init(&mutex_env->mutex_print, NULL) != 0)
        return (NULL);
    if (pthread_mutex_init(&mutex_env->mutex_schedule, NULL) != 0)
    {
        pthread_mutex_destroy(&mutex_env->mutex_print);
        return (NULL);
    }
    if (pthread_mutex_init(&mutex_env->mutex_state_sim, NULL) != 0)
    {
        pthread_mutex_destroy(&mutex_env->mutex_print);
        pthread_mutex_destroy(&mutex_env->mutex_schedule);
        return (NULL);
    }
    return (mutex_env);
}
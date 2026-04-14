#include "codexion.h"

void    free_args(t_args *args)
{
    if (args->schedule)
        free(args->schedule);
    if (args)
        free(args);
}
t_args  *init_args(char **argv)
{
    t_args *args;

    args = malloc(sizeof(t_args));
    if (!args)
        return (NULL);
    args->n_coders = atoi(argv[1]);
	args->t_burnout = atoi(argv[2]);
	args->t_compile = atoi(argv[3]);
	args->t_debug = atoi(argv[4]);
	args->t_refactor = atoi(argv[5]);
	args->n_compiles = atoi(argv[6]);
	args->t_cooldown = atoi(argv[7]);
    args->schedule = ft_strcpy(argv[8]);
    if (!args->schedule)
    {
        free_args(args);
        return (NULL);
    }
    return (args);
}
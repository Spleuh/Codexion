#include "codexion.h"

int check_arg_int(int time, int min)
{
	if (time < min || time > 2147483647)
		return -1;
	return 0;
}

int check_int(char *arg)
{
	int i;
	
	i = 0;
	if (!arg)
		return -1;	
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return -1;
		i++;
	}
	return 0;
}

int	parser(int argc, char **argv)
{
	int i;
	int result;
	int	tmp;

	result = 0;
	if (argc != 9)
		return -1;
	i = 1;
	while (i < 8)
	{
		if (check_int(argv[i]) < 0)
			return (-1);
		tmp = atoi(argv[i]);
		if (tmp < 1 || (i == 1 && tmp < 2))
			return (-1);
		i++;
	}
	if (!result && strcmp(argv[8], "fifo") != 0 && strcmp(argv[8], "edf") != 0)
		return (-1);
	return result;
}

t_data	*store_data(int argc, char **argv)
{
	t_data	*data;

	if (parser(argc, argv) < 0)
		return (NULL);
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->n_coders = atoi(argv[1]);
	data->t_burnout = atoi(argv[2]);
	data->t_compile = atoi(argv[3]);
	data->t_debug = atoi(argv[4]);
	data->t_refactor = atoi(argv[5]);
	data->n_compiles = atoi(argv[6]);
	data->t_cooldown = atoi(argv[7]);
	data->scheduler = ft_strcpy(argv[8]);
	data->stop_sim = 0;
	data->start_sim = 0;
	init_dongles(data);
	if (!data->scheduler)
	{
		free(data);
		return (NULL);
	}
	if (pthread_mutex_init(&data->mutex_print, NULL) != 0)
	{
		free(data);
		return (NULL);
	}
	if (pthread_mutex_init(&data->mutex_stop, NULL) != 0)
	{
		pthread_mutex_destroy(&data->mutex_print);
		free(data);
		return (NULL);
	}
	if (pthread_mutex_init(&data->mutex_start, NULL) != 0)
	{
		pthread_mutex_destroy(&data->mutex_print);
		pthread_mutex_destroy(&data->mutex_stop);
		free(data);
		return (NULL);
	}
	return (data);
}


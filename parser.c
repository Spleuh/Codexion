#include "codexion.h"
#include <string.h>
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
		if (arg[i] < 30 || arg[i] > 39)
			return -1;
		i++;
	}
	return 0;
}

int	parser(int argc, char **argv)
{
	int i;
	int *converted;
	int result;

	result = 0;
	converted = malloc(sizeof(int) * 7);
	if (!converted)
		return -1;
	if (argc != 9)
		return -1;
	i = 1;
	while(i < 8 && !result)
	{
		if (!check_int(argv[i]))
			return -1;
		converted[i - 1] = atoi(argv[i]);	
		if (!converted[i - 1])
			result = -1;
		i++;
	}
	if (!result && check_arg_int(converted[0], 2) < 0)
		result = -1;
	i = 1;
	while (!result && !check_arg_int(converted[i], 1) && i < 7)
		i++;
	free(converted);
	if (!result && i != 7)
		result = -1;
	if (!result && strcmp(argv[8], "fifo") != 0 && strcmp(argv[8], "edf") != 0)
		result = -1;
	result->stop_sim = False;
	return result;
}

t_data	*store_data(int argc, char **argv)
{
	t_data	*data;

	if (!*argv || parser(argc, argv) < 0)
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
	data->scheduler = argv[8];
	return (data);
}


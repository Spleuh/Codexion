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
int     get_size_digit(long l)
{
    int i;

    i = 0;
    while (l / 10 || l % 10)
	{
		l = l / 10;
        i++;
	}
    return (i);
}
char    *ft_ltoa(long l)
{
    char	*result;
    int		i;
	int		size;

	if (l == 0)
	{
		result = malloc(sizeof(char) * 2);
		if (!result)
			return (NULL);
		result[0]='0';
		result[1]='\n';
		return (result);
	}

	size = get_size_digit(l);
    result = malloc(sizeof(char) * (size + 1));
    if (!result)
		return (NULL);
	i = 0;
    while (l / 10 || l % 10)
	{
		result[i] = (l % 10) + 48;
		l = l / 10;
		i++;
	}
	result[i] = '\n';
	return (result);
}
void    print(t_data *data, char *str)
{
    pthread_mutex_lock(&data->mutex_print);
    fprintf(stdout, str, NULL);
    pthread_mutex_unlock(&data->mutex_print);
}
long    get_timestamp()
{
    struct  timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000L + time.tv_usec / 1000L);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	int		i;
	int		len1;
	int		len2;

	len1 = strlen(s1);
	len2 = strlen(s2);
	result = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!result)
		return (NULL);
	i = 0;	
	while (i < len1)
	{
		result[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < len2)
	{
		result[len1 + i] = s2[i];
		i++;
	}
	result[len1 + len2] = '\n';
	free(s1);
	free(s2);
	return (result);
}
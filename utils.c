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

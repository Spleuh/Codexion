/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsam <jsam@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 21:43:11 by jsam              #+#    #+#             */
/*   Updated: 2026/04/13 21:43:14 by jsam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "codexion.h"

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


int parser(int argc, char **argv)
{
    int i;
    int tmp;

    if (argc != 9)
        return (1);
    i = 1;
    while (i < 8)
    {
        if (check_int(argv[i]) < 0)
            return (1);
        tmp = atoi(argv[i]);
        if (tmp < 1)
            return (1);
        i++;
    }
    if (strcmp(argv[8], "fifo") != 0 && strcmp(argv[8], "edf") != 0)
        return (1);
    return (0);
}
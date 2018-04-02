/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadtest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:19:20 by fdexheim          #+#    #+#             */
/*   Updated: 2018/04/02 12:29:04 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../inc/alloc.h"
#include <string.h>
#include <stdio.h>

void				putstr_ghetto(char *str)
{
	write(1, str, strlen(str));
}

int					main()
{
	char			*strs[25];
	char			*strs2[25];
	char			*gogo;
	size_t			malloc_size = 32;
	int				i = 0;
	int				j = 0;

	pthread_t		allocator1;
	pthread_t		allocator2;



	while (i < 25)
	{
		if (pthread_create(&allocator1, NULL, (void*)malloc, (void*)malloc_size) != 0)
		{
			putstr_ghetto("error during thread creation, exiting\n");
			return (0);
		}
		if (pthread_create(&allocator2, NULL, (void*)malloc, (void*)malloc_size) != 0)
		{
			putstr_ghetto("error during thread creation, exiting\n");
			return (0);
		}
		pthread_join(allocator1, (void*)&strs[i]);
		pthread_join(allocator2, (void*)&strs2[i]);

		j = 0;
		while (j < malloc_size - 1)
		{
			strs[i][j] = 'x';
			strs2[i][j] = 'X';
			j++;
		}
		strs[i][malloc_size - 1] = '\0';
		strs2[i][malloc_size - 1] = '\0';
		i++;
	}

	show_alloc_mem_ex();
	putstr_ghetto(" --(Malloc ended)-- \n");
	pages_status();
	display_histo();
	getchar();

	for (int f = 12; f < 22; f++)
	{
		if (pthread_create(&allocator1, NULL, (void*)free, (void*)strs[f]) != 0)
		{
			putstr_ghetto("error during thread creation, exiting\n");
			return (0);
		}
		if (pthread_create(&allocator2, NULL, (void*)free, (void*)strs2[f]) != 0)
		{
			putstr_ghetto("error during thread creation, exiting\n");
			return (0);
		}
		pthread_join(allocator1, (void*)&strs[f]);
		pthread_join(allocator2, (void*)&strs2[f]);
	}
	show_alloc_mem_ex();
	pages_status();
	display_histo();
	putstr_ghetto(" --(Free ended)-- \n");
	return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   histo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:24:58 by fdexheim          #+#    #+#             */
/*   Updated: 2018/03/30 14:51:24 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/alloc.h"

extern t_mem g_mem;

void				init_gmem(void)
{
	int				k;

	k = 0;
	while (k < HISTORIC_SIZE)
	{
		g_mem.historic[k] = 0;
		g_mem.historic_size[k] = 0;
		k++;
	}
	g_mem.large_pages = NULL;
	g_mem.small_pages = NULL;
	g_mem.tiny_pages = NULL;
	g_mem.initialized = true;
}

void				tapi_roulant(void)
{
	int				k;

	k = HISTORIC_SIZE - 2;
	while (k >= 0)
	{
		g_mem.historic[k + 1] = g_mem.historic[k];
		g_mem.historic_size[k + 1] = g_mem.historic_size[k];
		k--;
	}
	g_mem.historic[0] = 0;
	g_mem.historic_size[0] = 0;
}

void				display_histo(void)
{
	int				k;

	if (g_mem.initialized == false)
		init_gmem();
	k = HISTORIC_SIZE;
	write(1, " == Recent memory allocations history ========= \n", 49);
	while (k >= 0)
	{
		if (g_mem.historic[k] == MALLOC_CODE)
			write(1, "malloc  | ", 11);
		else if (g_mem.historic[k] == REALLOC_CODE)
			write(1, "realloc | ", 11);
		else if (g_mem.historic[k] == FREE_CODE)
			write(1, "free    | ", 11);
		else if (g_mem.historic[k] == ERROR_CODE)
			write(1, "error ? | ", 11);
		if (g_mem.historic[k] != 0)
		{
			put_size_t_ghetto(g_mem.historic_size[k]);
			write(1, " bytes\n", 7);
		}
		k--;
	}
	write(1, " == End of Recent memory allocations history == \n", 49);
}

void				add_histo(unsigned char histo, size_t size)
{
	int				k;

	if (g_mem.initialized == false)
		init_gmem();
	k = HISTORIC_SIZE - 1;
	while (k >= 0 && g_mem.historic[k] != 0)
		k--;
	if (k < 0)
	{
		tapi_roulant();
		add_histo(histo, size);
		return ;
	}
	g_mem.historic[k] = histo;
	g_mem.historic_size[k] = size;
}

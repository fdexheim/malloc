/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pages_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 10:11:33 by fdexheim          #+#    #+#             */
/*   Updated: 2018/03/30 12:50:38 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/alloc.h"

extern t_mem g_mem;

size_t				count_allocated_blocs_in_page(t_page *pg)
{
	t_bloc			*bl;
	size_t			ret;

	if (pg == NULL)
		return (0);
	bl = pg->blocs;
	ret = 0;
	while (bl != NULL)
	{
		if (bl->is_allocated == true)
			ret++;
		bl = bl->next;
	}
	return (ret);
}


void				tiny_pages_status(void)
{
	size_t			blsubtotal;
	size_t			pgsubtotal;
	t_page			*pg;

	blsubtotal = 0;
	pgsubtotal = 0;
	pg = g_mem.tiny_pages;
	while (pg != NULL)
	{
		pgsubtotal++;
		blsubtotal += count_allocated_blocs_in_page(pg);
		pg = pg->next;
	}
	put_size_t_ghetto(blsubtotal);
	write(1, " allocated blocs in ", 20);
	put_size_t_ghetto(pgsubtotal);
	write(1, " tiny pages\n", 12);
}

void				small_pages_status(void)
{
	size_t			blsubtotal;
	size_t			pgsubtotal;
	t_page			*pg;

	blsubtotal = 0;
	pgsubtotal = 0;
	pg = g_mem.small_pages;
	while (pg != NULL)
	{
		pgsubtotal++;
		blsubtotal += count_allocated_blocs_in_page(pg);
		pg = pg->next;
	}
	put_size_t_ghetto(blsubtotal);
	write(1, " allocated blocs in ", 20);
	put_size_t_ghetto(pgsubtotal);
	write(1, " small pages\n", 13);
}

void				large_pages_status(void)
{
	size_t			blsubtotal;
	size_t			pgsubtotal;
	t_page			*pg;

	blsubtotal = 0;
	pgsubtotal = 0;
	pg = g_mem.large_pages;
	while (pg != NULL)
	{
		pgsubtotal++;
		blsubtotal += count_allocated_blocs_in_page(pg);
		pg = pg->next;
	}
	put_size_t_ghetto(blsubtotal);
	write(1, " allocated blocs in ", 20);
	put_size_t_ghetto(pgsubtotal);
	write(1, " large pages\n", 13);
}

void				pages_status(void)
{
	write(1, " == pages status =================\n", 35);
	large_pages_status();
	small_pages_status();
	tiny_pages_status();
	write(1, " == end of pages status ==========\n", 35);
}

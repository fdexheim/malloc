/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 08:37:52 by fdexheim          #+#    #+#             */
/*   Updated: 2018/03/29 15:31:53 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/alloc.h"

extern t_mem g_mem;

void				hexdmp_bloc(t_bloc *bl, t_size ptype)
{
	size_t			tmp;
	size_t			cap;
	unsigned char	*ptr;

	tmp = 0;
	ptr = (unsigned char*)DATA(bl);
	cap = ptype == LARGE ? bl->bloc_size : round_bloc_size(bl->bloc_size);
	while (tmp < cap)
	{
		if (tmp % 64 == 0 && tmp + 1 < cap)
		{
			write(1, "\n", 1);
			put_size_t_ghetto_hex((size_t)ptr);
		}
		write(1, " ", 1);
		put_unsigned_char_ghetto_hex((size_t)*ptr);
		tmp++;
		ptr++;
	}
}

void				hexdmp_page(t_page *pg)
{
	t_bloc			*bl;

	bl = pg->blocs;
	while (bl != NULL)
	{
		if (bl->is_allocated == false)
		{
			write(1, "\n*", 2);
			while (bl->is_allocated == false && bl->next != NULL)
				bl = bl->next;
		}
		hexdmp_bloc(bl, pg->ptype);
		if (bl->next == NULL)
			write(1, "\n", 1);
		bl = bl->next;
	}
}

void				show_alloc_mem_ex(void)
{
	t_page			*pg;

	switch_mutex_lock(true);
	pg = g_mem.large_pages;
	while (pg != NULL)
	{
		write(1, " -- Page for a single large allocation -- ", 42);
		hexdmp_page(pg);
		pg = pg->next;
	}
	pg = g_mem.small_pages;
	while (pg != NULL)
	{
		write(1, " -- Page of small allocations -- ", 33);
		hexdmp_page(pg);
		pg = pg->next;
	}
	pg = g_mem.tiny_pages;
	while (pg != NULL)
	{
		write(1, " -- Page of tiny allocations -- ", 32);
		hexdmp_page(pg);
		pg = pg->next;
	}
	switch_mutex_lock(false);
}

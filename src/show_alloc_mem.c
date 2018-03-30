/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 13:39:48 by fdexheim          #+#    #+#             */
/*   Updated: 2018/03/30 14:33:53 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/alloc.h"

extern t_mem g_mem;

void				print_bloc(t_bloc *bl)
{
	write(1, "0x", 2);
	put_size_t_ghetto_hex((size_t)DATA(bl));
	write(1, " - 0x", 5);
	put_size_t_ghetto_hex((size_t)DATA(bl) + bl->bloc_size);
	write(1, " : ", 3);
	put_size_t_ghetto(bl->bloc_size);
	write(1, " octets\n", 8);
}

void				print_page_header(t_page *pg)
{
	if (pg->ptype == TINY)
		write(1, "TINY : 0x", 9);
	else if (pg->ptype == SMALL)
		write(1, "SMALL : 0x", 10);
	else if (pg->ptype == LARGE)
		write(1, "LARGE : 0x", 10);
	put_size_t_ghetto_hex((size_t)pg);
	write(1, "\n", 1);
}

size_t				print_pages(t_page *pg)
{
	t_bloc			*bl;
	size_t			subtotal;

	subtotal = 0;
	while (pg != NULL)
	{
		print_page_header(pg);
		bl = pg->blocs;
		while (bl)
		{
			if (bl->is_allocated == true)
			{
				print_bloc(bl);
				subtotal += bl->bloc_size;
			}
			bl = bl->next;
		}
		pg = pg->next;
	}
	return (subtotal);
}

void				show_alloc_mem(void)
{
	size_t			total;

	switch_mutex_lock(true);
	total = 0;
	if (g_mem.tiny_pages != NULL)
		total += print_pages(g_mem.tiny_pages);
	if (g_mem.small_pages != NULL)
		total += print_pages(g_mem.small_pages);
	if (g_mem.large_pages != NULL)
		total += print_pages(g_mem.large_pages);
	write(1, "Total : ", 8);
	put_size_t_ghetto(total);
	write(1, " octets\n", 8);
	switch_mutex_lock(false);
}

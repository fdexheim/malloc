/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pages_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 08:49:37 by fdexheim          #+#    #+#             */
/*   Updated: 2018/03/16 09:43:18 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/alloc.h"

extern t_mem g_mem;

bool			is_page_sorted(t_page *pg)
{
	t_bloc		*bl;
	int			nb_changes;
	bool		flip;

	bl = pg->blocs;
	flip = bl->is_allocated;
	nb_changes = 0;
	while (bl)
	{
		if (bl->is_allocated != flip)
		{
			flip = bl->is_allocated;
			nb_changes++;
		}
		bl = bl->next;
	}
	if ((nb_changes > 1)
			|| (nb_changes == 1 && pg->blocs->is_allocated == false))
	{
		return (false);
	}
	return (true);
}

t_bloc			*search_allocated_bloc_from_data_ptr(void *ptr, t_page *pg)
{
	t_bloc		*bl;

	if (pg == NULL || ptr == NULL)
		return (NULL);
	while (pg)
	{
		bl = pg->blocs;
		while (bl)
		{
			if (ptr == DATA(bl))
				return (bl);
			bl = bl->next;
		}
		pg = pg->next;
	}
	return (NULL);
}

t_bloc			*full_search_allocated_bloc_from_data_ptr(void *ptr)
{
	t_bloc		*bl;

	if (ptr == NULL)
		return (NULL);
	bl = search_allocated_bloc_from_data_ptr(ptr, g_mem.large_pages);
	if (bl != NULL)
		return (bl);
	bl = search_allocated_bloc_from_data_ptr(ptr, g_mem.small_pages);
	if (bl != NULL)
		return (bl);
	bl = search_allocated_bloc_from_data_ptr(ptr, g_mem.tiny_pages);
	if (bl != NULL)
		return (bl);
	return (NULL);
}

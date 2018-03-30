/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pages.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 08:56:55 by fdexheim          #+#    #+#             */
/*   Updated: 2018/03/16 09:43:16 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/alloc.h"

extern t_mem g_mem;

bool			check_full_free_page(t_page *pg)
{
	t_bloc		*bl;

	bl = pg->blocs;
	while (bl)
	{
		if (bl->is_allocated == true)
		{
			return (false);
		}
		bl = bl->next;
	}
	return (true);
}

t_bloc			*find_allocated_bloc_in_page(t_bloc *start)
{
	t_bloc		*bl;

	bl = start;
	while (bl != NULL)
	{
		if (bl->is_allocated == true)
		{
			return (bl);
		}
		bl = bl->next;
	}
	return (NULL);
}

t_bloc			*find_unallocated_bloc_in_page(t_bloc *start)
{
	t_bloc		*bl;

	bl = start;
	while (bl != NULL)
	{
		if (bl->is_allocated == false)
		{
			return (bl);
		}
		bl = bl->next;
	}
	return (NULL);
}

t_bloc			*find_unallocated_bloc_in_page_list(t_page *ptr)
{
	t_bloc		*bl;

	if (ptr == NULL)
		return (NULL);
	while (ptr)
	{
		bl = find_unallocated_bloc_in_page(ptr->blocs);
		if (bl != NULL)
		{
			return (bl);
		}
		ptr = ptr->next;
	}
	return (NULL);
}

t_bloc			*find_unallocated_bloc(size_t size)
{
	t_page		*pg;

	pg = get_list_from_size(size);
	return (find_unallocated_bloc_in_page_list(pg));
}

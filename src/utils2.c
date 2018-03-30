/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 13:47:42 by fdexheim          #+#    #+#             */
/*   Updated: 2018/03/30 13:42:28 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/alloc.h"

extern t_mem g_mem;

t_size				get_ptype_from_data_ptr(void *ptr)
{
	if (search_allocated_bloc_from_data_ptr(ptr, g_mem.large_pages) != NULL)
		return (LARGE);
	else if (search_allocated_bloc_from_data_ptr(ptr,
				g_mem.small_pages) != NULL)
		return (SMALL);
	else
		return (TINY);
}

t_size				get_ptype_from_size(size_t size)
{
	if (size <= TINY_MAX_SIZE)
		return (TINY);
	else if (size <= SMALL_MAX_SIZE)
		return (SMALL);
	else
		return (LARGE);
}

t_page				*get_list_from_size(size_t size)
{
	if (size <= TINY_MAX_SIZE)
	{
		return (g_mem.tiny_pages);
	}
	else if (size <= SMALL_MAX_SIZE)
	{
		return (g_mem.small_pages);
	}
	else
	{
		return (g_mem.large_pages);
	}
}

size_t				get_page_list_size(t_page *pg)
{
	size_t			ret;

	ret = 0;
	while (pg != NULL)
	{
		pg = pg->next;
		ret++;
	}
	return (ret);
}

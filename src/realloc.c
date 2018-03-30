/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 13:34:26 by fdexheim          #+#    #+#             */
/*   Updated: 2018/03/30 13:55:38 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/alloc.h"

extern t_mem g_mem;

void		*realloc_bloc(void *ptr, size_t size)
{
	t_bloc	*src;
	t_bloc	*dst;

	src = full_search_allocated_bloc_from_data_ptr(ptr);
	if (find_unallocated_bloc(size) == NULL)
	{
		build_page(size);
	}
	dst = find_unallocated_bloc(size);
	if (dst != NULL)
	{
		dst->bloc_size = size;
		dst->is_allocated = true;
		copy_data(DATA(src), DATA(dst), min_size(size, src->bloc_size));
		src->is_allocated = false;
		src->bloc_size = 0;
		return (DATA(dst));
	}
	return (NULL);
}

void		*realmalloc(size_t size)
{
	t_bloc			*bl;

	switch_mutex_lock(true);
	bl = find_unallocated_bloc(size);
	if (bl == NULL)
	{
		build_page(size);
	}
	bl = find_unallocated_bloc(size);
	if (bl == NULL)
	{
		errno = ENOMEM;
		switch_mutex_lock(false);
		return (NULL);
	}
	bl->bloc_size = size;
	bl->is_allocated = true;
	switch_mutex_lock(false);
	return (DATA(bl));
}

void		*realloc2(void *ptr, size_t size)
{
	void	*ret;

	if (full_search_allocated_bloc_from_data_ptr(ptr) == NULL)
	{
		add_histo(ERROR_CODE, 0);
		return (NULL);
	}
	else if (get_ptype_from_data_ptr(ptr) == get_ptype_from_size(size)
			&& get_ptype_from_size(size) != LARGE)
	{
		full_search_allocated_bloc_from_data_ptr(ptr)->bloc_size = size;
		return (ptr);
	}
	else
	{
		ret = realloc_bloc(ptr, size);
		check_erase_large_page();
		check_erase_small_page();
		check_erase_tiny_page();
		return (ret);
	}
}

void		*realloc(void *ptr, size_t size)
{
	void	*ret;

	switch_mutex_lock(true);
	add_histo(REALLOC_CODE, size);
	if (ptr == NULL)
	{
		switch_mutex_lock(false);
		ret = realmalloc(size);
		return (ret);
	}
	else
	{
		ret = realloc2(ptr, size);
	}
	switch_mutex_lock(false);
	return (ret);
}

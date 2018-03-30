/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 08:31:14 by fdexheim          #+#    #+#             */
/*   Updated: 2018/03/30 09:51:48 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/alloc.h"

t_mem				g_mem = {0, 0, 0, false, false, { 0 }, { 0 } };
pthread_mutex_t		g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;

void				switch_mutex_lock(bool lock)
{
	if (lock == true)
	{
		pthread_mutex_lock(&g_malloc_mutex);
	}
	else if (lock == false)
	{
		pthread_mutex_unlock(&g_malloc_mutex);
	}
}

void				*malloc(size_t size)
{
	t_bloc			*bl;

	switch_mutex_lock(true);
	add_histo(MALLOC_CODE, size);
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

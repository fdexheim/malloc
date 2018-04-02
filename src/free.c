/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 13:34:20 by fdexheim          #+#    #+#             */
/*   Updated: 2018/04/02 12:23:29 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/alloc.h"

extern t_mem g_mem;

void			check_erase_large_page(void)
{
	t_page		*tmp;
	t_page		*tofree;

	while (g_mem.large_pages != NULL
			&& check_full_free_page(g_mem.large_pages) == true)
	{
		tmp = g_mem.large_pages;
		g_mem.large_pages = tmp->next;
		if (munmap(tmp, tmp->page_size) == -1)
			write(1, "MUNMAP ERROR!\n", 14);
	}
	tmp = g_mem.large_pages;
	while (tmp)
	{
		if (tmp->next != NULL && check_full_free_page(tmp->next))
		{
			tofree = tmp->next;
			tmp->next = tmp->next->next;
			if (munmap(tofree, tofree->page_size) == -1)
				write(1, "MUNMAP ERROR!\n", 14);
		}
		tmp = tmp->next;
	}
}

void			check_erase_small_page(void)
{
	t_page		*tmp;
	t_page		*tofree;

	while (g_mem.small_pages != NULL
			&& check_full_free_page(g_mem.small_pages) == true)
	{
		tmp = g_mem.small_pages;
		g_mem.small_pages = tmp->next;
		if (munmap(tmp, tmp->page_size) == -1)
			write(1, "MUNMAP ERROR!\n", 14);
	}
	tmp = g_mem.small_pages;
	while (tmp != NULL)
	{
		if (tmp->next != NULL && check_full_free_page(tmp->next))
		{
			tofree = tmp->next;
			tmp->next = tmp->next->next;
			if (munmap(tofree, tofree->page_size) == -1)
				write(1, "MUNMAP ERROR!\n", 14);
		}
		tmp = tmp->next;
	}
}

void			check_erase_tiny_page(void)
{
	t_page		*tmp;
	t_page		*tofree;

	while (g_mem.tiny_pages != NULL
			&& check_full_free_page(g_mem.tiny_pages) == true)
	{
		tmp = g_mem.tiny_pages;
		g_mem.tiny_pages = tmp->next;
		if (munmap(tmp, tmp->page_size) == -1)
			write(1, "MUNMAP ERROR!\n", 14);
	}
	tmp = g_mem.tiny_pages;
	while (tmp != NULL)
	{
		if (tmp->next != NULL && check_full_free_page(tmp->next))
		{
			tofree = tmp->next;
			tmp->next = tmp->next->next;
			if (munmap(tofree, tofree->page_size) == -1)
				write(1, "MUNMAP ERROR!\n", 14);
		}
		tmp = tmp->next;
	}
}

void			free2(void *ptr)
{
	t_bloc		*bl;

	bl = search_allocated_bloc_from_data_ptr(ptr, g_mem.large_pages);
	if (bl != NULL)
	{
		bl->is_allocated = false;
		add_histo(FREE_CODE, bl->bloc_size);
		check_erase_large_page();
		return ;
	}
	bl = search_allocated_bloc_from_data_ptr(ptr, g_mem.small_pages);
	if (bl != NULL)
	{
		bl->is_allocated = false;
		add_histo(FREE_CODE, bl->bloc_size);
		check_erase_small_page();
		return ;
	}
	bl = search_allocated_bloc_from_data_ptr(ptr, g_mem.tiny_pages);
	if (bl != NULL)
	{
		bl->is_allocated = false;
		add_histo(FREE_CODE, bl->bloc_size);
		check_erase_tiny_page();
	}
}

void			free(void *ptr)
{
	switch_mutex_lock(true);
	if (ptr == NULL || full_search_allocated_bloc_from_data_ptr(ptr) == NULL)
	{
		add_histo(ERROR_CODE, 0);
		switch_mutex_lock(false);
		return ;
	}
	free2(ptr);
	switch_mutex_lock(false);
}

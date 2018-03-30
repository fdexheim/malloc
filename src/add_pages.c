/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_pages.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 15:07:35 by fdexheim          #+#    #+#             */
/*   Updated: 2018/03/16 16:09:19 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/alloc.h"

extern t_mem g_mem;

void			add_tiny_page(t_page *page)
{
	t_page		*pg;

	if (g_mem.tiny_pages == NULL)
		g_mem.tiny_pages = page;
	else
	{
		pg = g_mem.tiny_pages;
		while (pg->next != NULL)
			pg = pg->next;
		pg->next = page;
		page->next = NULL;
	}
}

void			add_small_page(t_page *page)
{
	t_page		*pg;

	if (g_mem.small_pages == NULL)
		g_mem.small_pages = page;
	else
	{
		pg = g_mem.small_pages;
		while (pg->next != NULL)
			pg = pg->next;
		pg->next = page;
		page->next = NULL;
	}
}

void			add_large_page(t_page *page)
{
	t_page		*pg;

	if (g_mem.large_pages == NULL)
		g_mem.large_pages = page;
	else
	{
		pg = g_mem.large_pages;
		while (pg->next != NULL)
			pg = pg->next;
		pg->next = page;
		page->next = NULL;
	}
}

void			add_page(t_page *page)
{
	if (page->ptype == TINY)
		add_tiny_page(page);
	else if (page->ptype == SMALL)
		add_small_page(page);
	else if (page->ptype == LARGE)
		add_large_page(page);
}

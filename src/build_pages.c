/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pages.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 12:40:23 by fdexheim          #+#    #+#             */
/*   Updated: 2018/03/30 14:24:31 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/alloc.h"

extern t_mem g_mem;

size_t				get_closest_page_size(size_t size)
{
	size_t			p;
	unsigned int	i;

	i = 0;
	p = PAGE_OVERHEAD + (round_bloc_per_page(size) * (round_bloc_size(size)
			+ BLOC_OVERHEAD));
	while (i * getpagesize() < p)
		i++;
	return (i * getpagesize());
}

void				build_page_ter(size_t size, t_page *ret)
{
	unsigned int	i;
	t_bloc			*bl;
	unsigned char	*a;

	a = (unsigned char*)ret;
	ret->blocs = (t_bloc*)(a + PAGE_OVERHEAD);
	bl = ret->blocs;
	i = 0;
	while (i < round_bloc_per_page(size))
	{
		i++;
		a = (unsigned char*)bl;
		bl->is_allocated = false;
		if (i == round_bloc_per_page(size))
		{
			bl->next = NULL;
			return ;
		}
		bl->next = (t_bloc*)(a + BLOC_OVERHEAD + round_bloc_size(size));
		bl = bl->next;
	}
}

t_page				*build_page_bis(size_t size)
{
	t_page			*ret;

	ret = (t_page*)mmap(NULL, get_closest_page_size(size),
			PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (ret == MAP_FAILED)
		return (NULL);
	build_page_ter(size, ret);
	ret->page_size = get_closest_page_size(size);
	ret->ptype = get_ptype_from_size(size);
	ret->next = NULL;
	return (ret);
}

void				build_page(size_t size)
{
	t_page			*page;

	page = build_page_bis(size);
	if (page == NULL)
	{
		errno = ENOMEM;
		g_mem.failed = true;
		return ;
	}
	add_page(page);
}

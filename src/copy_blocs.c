/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_blocs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 09:29:33 by fdexheim          #+#    #+#             */
/*   Updated: 2018/03/16 09:43:21 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/alloc.h"

extern t_mem g_mem;

void				copy_data(void *src, void *dst, size_t size)
{
	char			*s;
	char			*d;
	unsigned int	i;

	if (size == 0 || src == NULL || dst == NULL)
		return ;
	s = (char*)src;
	d = (char*)dst;
	i = 0;
	while (i < size)
	{
		*d = *s;
		d++;
		s++;
		i++;
	}
}

void				move_bloc(t_bloc *src, t_bloc *dst)
{
	if (src == NULL || dst == NULL)
		return ;
	copy_data(DATA(src), DATA(dst), src->bloc_size);
	dst->bloc_size = src->bloc_size;
	dst->is_allocated = true;
	src->is_allocated = false;
}

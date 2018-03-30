/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 14:45:06 by fdexheim          #+#    #+#             */
/*   Updated: 2018/03/09 14:29:08 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/alloc.h"

extern t_mem g_mem;

size_t				get_round_size_from_ptype(t_size ptype)
{
	if (ptype == TINY)
		return (TINY_MAX_SIZE);
	else if (ptype == SMALL)
		return (SMALL_MAX_SIZE);
	return (0);
}

size_t				round_bloc_per_page(size_t size)
{
	if (size <= TINY_MAX_SIZE)
		return (NB_TINY_BLOCS);
	else if (size <= SMALL_MAX_SIZE)
		return (NB_SMALL_BLOCS);
	else
		return (NB_LARGE_BLOCS);
}

size_t				round_bloc_size(size_t size)
{
	if (size <= TINY_MAX_SIZE)
		return (TINY_MAX_SIZE);
	else if (size <= SMALL_MAX_SIZE)
		return (SMALL_MAX_SIZE);
	else
		return (size);
}

size_t				min_size(size_t s1, size_t s2)
{
	if (s1 < s2)
		return (s1);
	return (s2);
}

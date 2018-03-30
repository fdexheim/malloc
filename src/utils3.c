/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 09:42:41 by fdexheim          #+#    #+#             */
/*   Updated: 2018/03/29 08:35:51 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/alloc.h"

extern t_mem g_mem;

void				putchar_ghetto(char c)
{
	write(1, &c, 1);
}

void				put_size_t_ghetto(size_t src)
{
	if (src >= 10)
		put_size_t_ghetto(src / 10);
	putchar_ghetto(src % 10 + '0');
}

void				put_size_t_ghetto_hex(size_t src)
{
	const char		hexa[] = "0123456789ABCDEF";

	if (src >= 16)
		put_size_t_ghetto_hex(src / 16);
	putchar_ghetto(hexa[src % 16]);
}

void				put_unsigned_char_ghetto_hex(unsigned char c)
{
	const char		hexa[] = "0123456789ABCDEF";

	if (c <= 0xf)
	{
		write(1, "0", 1);
		putchar_ghetto(hexa[c % 16]);
	}
	else
	{
		putchar_ghetto(hexa[c / 16]);
		putchar_ghetto(hexa[c % 16]);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 09:23:12 by fdexheim          #+#    #+#             */
/*   Updated: 2018/03/09 13:43:03 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/alloc.h"
#include <string.h>

#define M (1024 * 1024)

void		print(char * s)
{
	write(1, s, strlen(s));
}

int			main(void)
{
	char	*addr1;
	char	*addr3;

	addr1 = (char*)malloc(16 * M);
	strcpy(addr1, "Bonjours\n");
	print(addr1);
	addr3 = (char*)realloc(addr1, 128 * M);
	addr3[127*M] = 42;
	print(addr3);
	return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testshowX.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 12:42:32 by fdexheim          #+#    #+#             */
/*   Updated: 2018/03/30 14:50:30 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/alloc.h"
#include <string.h>

#define M (1024 * 1024)

int			main(void)
{
	char	*addr1;
	char	*addr2;
	char	*addr3;

	addr1 = (char*)malloc(8);
	addr2 = (char*)malloc(8);
	addr3 = (char*)malloc(8);

	addr1[6] = 1;
	addr1[7] = '\0';
	addr2[6] = 1;
	addr2[7] = '\0';
	addr3[6] = 1;
	addr3[7] = '\0';

	show_alloc_mem_ex();
	free(addr2);

	write(1, "\nfree addr2...\n\n", 16);

	show_alloc_mem_ex();

	display_histo();
	return 0;
}

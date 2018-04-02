/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 08:42:28 by fdexheim          #+#    #+#             */
/*   Updated: 2018/04/02 12:15:50 by fdexheim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOC_H
# define ALLOC_H

# define BLOC_OVERHEAD 24
# define PAGE_OVERHEAD 32

# define TINY_MAX_SIZE 64
# define NB_TINY_BLOCS 256

# define SMALL_MAX_SIZE 1024
# define NB_SMALL_BLOCS 256

# define NB_LARGE_BLOCS 1

# define HISTORIC_SIZE 50
# define ERROR_CODE 1
# define MALLOC_CODE 2
# define REALLOC_CODE 3
# define FREE_CODE 4
# define DATA(T) (void*)((unsigned char*)T + BLOC_OVERHEAD)

# include <sys/mman.h>
# include <errno.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>

typedef enum			e_size
{
	TINY,
	SMALL,
	LARGE
}						t_size;

typedef struct			s_bloc
{
	struct s_bloc		*next;
	size_t				bloc_size;
	bool				is_allocated;
}						t_bloc;

typedef struct			s_page
{
	struct s_page		*next;
	size_t				page_size;
	t_size				ptype;
	t_bloc				*blocs;
}						t_page;

typedef struct			s_mem
{
	t_page				*large_pages;
	t_page				*small_pages;
	t_page				*tiny_pages;
	bool				failed;
	bool				initialized;
	char				historic[HISTORIC_SIZE];
	size_t				historic_size[HISTORIC_SIZE];
}						t_mem;

void					switch_mutex_lock(bool lock);

t_page					*get_list_from_size(size_t size);
size_t					get_closest_page_size(size_t size);
t_size					get_ptype_from_size(size_t size);
t_size					get_ptype_from_data_ptr(void *ptr);
bool					check_full_free_page(t_page *pg);
size_t					get_page_list_size(t_page *pg);
size_t					get_round_size_from_ptype(t_size ptype);
size_t					round_bloc_size(size_t size);
size_t					round_bloc_per_page(size_t size);
size_t					min_size(size_t s1, size_t s2);
void					put_size_t_ghetto_hex(size_t src);
void					put_size_t_ghetto(size_t src);
void					put_unsigned_char_ghetto_hex(unsigned char c);
void					copy_data(void *src, void *dst, size_t size);
void					move_bloc(t_bloc *src, t_bloc *dst);
void					check_erase_tiny_page(void);
void					check_erase_small_page(void);
void					check_erase_large_page(void);
void					add_page(t_page *page);
void					build_page(size_t size);
void					pages_status(void);
t_bloc					*search_allocated_bloc_from_data_ptr(void *ptr,
		t_page *pg);
t_bloc					*full_search_allocated_bloc_from_data_ptr(void *ptr);
t_bloc					*find_unallocated_bloc(size_t size);
t_bloc					*find_unallocated_bloc_in_page_list(t_page *ptr);
t_bloc					*find_unallocated_bloc_in_page(t_bloc *start);
t_bloc					*find_allocated_bloc_in_page(t_bloc *start);

void					init_gmem(void);
void					display_histo(void);
void					add_histo(unsigned char histo, size_t size);
void					show_alloc_mem_ex(void);

void					show_alloc_mem(void);
void					free(void *ptr);
void					*malloc(size_t size);
void					*realloc(void *ptr, size_t size);

#endif

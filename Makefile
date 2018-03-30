# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdexheim <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/26 14:02:22 by fdexheim          #+#    #+#              #
#    Updated: 2018/03/30 15:01:39 by fdexheim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME =	libft_malloc_$(HOSTTYPE).so
LINK = libft_malloc.so

INCLUDES_PATH = ./inc/

SRC_PATH = ./src/
SRC_NAME =	add_pages.c build_pages.c check_pages.c check_pages_2.c \
		copy_blocs.c free.c histo.c malloc.c pages_status.c \
		realloc.c show_alloc_mem.c show_alloc_mem2.c utils.c utils2.c utils3.c \

OBJ_PATH = ./obj/
OBJ_NAME =	$(SRC_NAME:.c=.o)

CC =	gcc
CC_FLAGS = -Wall -Werror -Wextra
LINK_FLAGS = -shared -lpthread

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

all:		$(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@echo "\033[1;32;m[$@]\033[0m : " | tr -d '\n'
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CC) $(CC_FLAGS) -I$(INCLUDES_PATH) -o $@ -c $<

$(NAME): $(OBJ)
	@$(CC) $(LINK_FLAGS) -o $@ $(OBJ)
	@echo "\033[1;32;m[Compilation Successful]\033[0m"
	@echo "\033[1;36;m$(NAME)\033[1;32;m ready to go !\033[0m"
	@rm -f $(LINK)
	@ln -s $(NAME) $(LINK)

clean:
	@echo "\033[0;33;m[Clean]\033[0m              : " | tr -d '\n'
	rm -f $(OBJ)

fclean:		clean
	@echo "\033[0;31;m[Deleting $(LINK)]\033[0m : " | tr -d '\n'
	rm -f $(LINK)
	@echo "\033[0;31;m[Deleting $(NAME)]\033[0m : " | tr -d '\n'
	rm -f $(NAME)
	@rm -rf $(OBJ_PATH)
	@rm -f test0
	@rm -f test1
	@rm -f test2
	@rm -f test3
	@rm -f test3++
	@rm -f test4
	@rm -f test5
	@rm -f testshowX
	@rm -f threadtestX

re:			fclean all

test:		re
	gcc -o test0 test/test0.c
	gcc -o test1 test/test1.c
	gcc -o test2 test/test2.c
	gcc -o test3 test/test3.c
	gcc -o test3++ test/test3++.c
	gcc -o test4 test/test4.c
	gcc -o test5 test/test5.c -L. $(LINK)
	gcc -o testshowX test/testshowX.c -L. $(LINK)
	gcc -o threadtestX test/threadtestX.c -L. $(LINK)

.PHONY:		all clean fclean re test

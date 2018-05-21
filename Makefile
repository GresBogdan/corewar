# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgres <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/20 12:56:36 by bgres             #+#    #+#              #
#    Updated: 2018/02/20 12:56:40 by bgres            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = my_asm

SRC = asm.c pars_two.c

OBJ = $(SRC:.c=.o)

MAKELIB = make -C libftprintf/

HEADER = asm.h

LIBPATH = libftprintf/libftprintf.a

SFLAG = -c  -O3 -Os
#-Wall -Werror -Wextra
.PHONY: all clean fclean re

.NOTPARALLEL: all clean fclean re

all: $(NAME)

$(NAME): $(LIBPATH) $(OBJ)
	gcc -o $(NAME) $(OBJ) $(LIBPATH) 

$(LIBPATH): 
	make -C libftprintf/

%.o: %.c $(HEADER)
	gcc $(SFLAG)  $< -o $@ 

clean: 
	rm -f $(OBJ)
	make -C libftprintf/ clean

fclean: clean
	rm -f $(NAME)
	make -C libftprintf/ fclean

re: fclean all

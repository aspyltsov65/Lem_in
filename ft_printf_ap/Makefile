# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apyltsov <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/22 20:20:54 by apyltsov          #+#    #+#              #
#    Updated: 2018/02/22 20:20:56 by apyltsov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
LIBFT_DIR = ../libft
LIBFT = $(LIBFT_DIR)/libft.a
SRCFILL = ft_printf.c\
		ft_parse.c\
		flags.c\
		ultoa_base.c\
		put_flags.c\
		fl_cs.c\
		unicode.c\
		ft_specifier.c\
		flag_wigth.c
SOURCES = $(addprefix ./, $(SRCFILL))
OBJECTS = $(addprefix ./obj/, $(SRCFILL:.c=.o))

CC = gcc
FLAGS ?= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	ar rc $(NAME) $(OBJECTS) $(LIBFT_DIR)/*.o
	ranlib $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

obj:
	mkdir obj/

obj/%.o: ./%.c | obj
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf obj/
	make fclean -C $(LIBFT_DIR)
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re


# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apyltsov <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/07 17:31:40 by apyltsov          #+#    #+#              #
#    Updated: 2018/09/07 17:31:43 by apyltsov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= lem-in
LIBFTDIR := libft/
LIBFT = $(LIBFTDIR)/libft.a
PRINTF = ft_printf
SRCFILE = src/*.c
OBJECTS = $(addprefix ./obj/, $(SRCFILE:.c=./obj.o))
CC = gcc
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): obj $(OBJECTS)
	@make -C $(LIBFTDIR)
	@make -C $(PRINTF)
	@$(CC) $(FLAGS) -o $(NAME) $(SRCFILE) $(LIBFT) $(PRINTF)/libftprintf.a

obj:
	mkdir -p obj/

obj/%.o: ./%.c | obj
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -rf obj/
	@make clean -C $(LIBFTDIR)
	@make clean -C $(PRINTF)

fclean: clean
	@make fclean -C $(LIBFTDIR)
	@make fclean -C $(PRINTF)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

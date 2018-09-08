# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apyltsov <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/07 17:31:40 by apyltsov          #+#    #+#              #
#    Updated: 2018/09/08 13:53:40 by apyltsov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= lem-in

OBJ_DIR = ./obj/
INC_DIR = ./inc/
SRC_DIR = ./src/

LIBFTDIR := ./libft/
PRINTF_DIR = ./ft_printf/

LIBFT = $(LIBFTDIR)/libft.a
PRINTF = $(PRINTF_DIR)/libftprintf.a

SRCFILE = algor.c get_next_line.c go_ants.c parse_link.c reading.c check.c parse_room.c validation.c

OBJECTS = $(addprefix $(OBJ_DIR), $(SRCFILE:.c=.o))

CC = gcc
FLAGS = -Wall -Wextra -Werror
HDR_FLAGS = -I $(INC_DIR)

all: $(NAME)

$(NAME): $(LIBFT) $(PRINTF) $(OBJECTS)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJECTS) $(LIBFT) $(PRINTF)

$(OBJECTS): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: %.c
	@$(CC) -c $< -o $@ $(FLAGS) $(HDR_FLAGS)

$(LIBFT):
	@make -C $(LIBFTDIR)

$(PRINTF):
	@make -C $(PRINTF_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFTDIR)
	@make clean -C $(PRINTF_DIR)

fclean: clean
	@make fclean -C $(LIBFTDIR)
	@make fclean -C $(PRINTF_DIR)
	@rm -f $(NAME)

re: fclean all

vpath %.c $(SRC_DIR)

.PHONY: all clean fclean re

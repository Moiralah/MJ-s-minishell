# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/28 15:46:22 by huidris           #+#    #+#              #
#    Updated: 2025/02/10 21:36:02 by huidris          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= builtin
FLAGS	= -Wall -Wextra -Werror#-fsanitize=address -g3 -ggdb

CC	= gcc

SRC_DIR	= .
SRC	= $(wildcard $(SRC_DIR)/*.c)

LIBFT	= ../libft
LIBFT_A	= ../libft/libft.a

OBJ_DIR	= obj
OBJS	= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

LINKS	= -lft -L $(LIBFT)

$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(FLAGS) $(OBJS) $(LINKS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(LIBFT_A):
	make -C $(LIBFT)

all: $(NAME)

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re

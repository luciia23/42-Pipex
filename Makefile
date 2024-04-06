# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/13 12:01:22 by lcollado          #+#    #+#              #
#    Updated: 2024/04/05 20:54:02 by lcollado         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

BIN = bin
DIR_SRC = src

INCLUDE = -I inc
CFLAGS = -g -Wall -Werror -Wextra
CC = gcc $(CFLAGS) $(INCLUDE)

# ------- Valgrind Rule -------
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose
# -fsanitize=address -g3

# ------- LIBFT -------
LIBFT_DIR = libft
LIBFT_PATH = $(LIBFT_DIR)/libft.a
LIBFT_MAKE = Makefile
LFLAGS:= -L $(LIBFT_DIR) -lft

# ------- COLORS -------
RED				=	\033[0;31m
GREEN			=	\033[0;32m

SRC = 	main.c\
		parse.c\
		io.c\
		pipex.c\
		utils.c\
		
OBJS = $(SRC:%.c=$(BIN)/%.o)

# ------- RULES / TRIGGERS
all: $(NAME)

$(NAME) : $(LIBFT_PATH) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME) 
	@echo "   - $(NAME) ${GREEN}compiled [OK]${GREEN}\n"

$(BIN)/%.o : $(DIR_SRC)/%.c
	@mkdir -p $(dir $@)
	@$(CC) -c $< -o $@

$(LIBFT_PATH):
	@cd $(LIBFT_DIR) && make
	@echo "   - LIBFT ${GREEN}compiled [OK]${GREEN}\n"

clean:
	@make -C $(LIBFT_DIR) -f $(LIBFT_MAKE) fclean
	rm -rf $(BIN)

fclean: clean
	rm -rf $(OBJS) $(NAME)

re : fclean all

valgrind: $(NAME)
	@echo "Running Valgrind..."
	@valgrind $(VALGRIND_FLAGS) ./$(NAME) []

.PHONY: all re clean fclean valgrind
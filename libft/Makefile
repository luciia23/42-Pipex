# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/21 16:22:26 by lcollado          #+#    #+#              #
#    Updated: 2024/02/10 12:30:31 by lcollado         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC =	ft_isalpha.c\
		ft_isdigit.c\
		ft_isalnum.c\
		ft_isascii.c\
		ft_isprint.c\
		ft_strlen.c\
		ft_memset.c\
		ft_bzero.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_strlcpy.c\
		ft_strlcat.c\
		ft_toupper.c\
		ft_tolower.c\
		ft_strchr.c\
		ft_strrchr.c\
		ft_strncmp.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_strnstr.c\
		ft_atoi.c\
		ft_calloc.c\
		ft_strdup.c\
		ft_putchar_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_putstr_fd.c\
		ft_substr.c\
		ft_strjoin.c\
		ft_itoa.c\
		ft_split.c\
		ft_strtrim.c\
		ft_strmapi.c\
		ft_striteri.c\
		get_next_line.c\
		gnl_strchr.c\
		gnl_strjoin.c

OBJS = $(SRC:.c=.o)

SRC_BONUS = ft_lstnew_bonus.c\
			ft_lstadd_front_bonus.c\
			ft_lstsize_bonus.c\
			ft_lstlast_bonus.c\
			ft_lstadd_back_bonus.c\
			ft_lstdelone_bonus.c\
			ft_lstclear_bonus.c\
			ft_lstiter_bonus.c\
			ft_lstmap_bonus.c

OBJS_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(SRC) -c
	ar crs $(NAME) $(OBJS)

bonus: $(OBJS_BONUS)
	ar crs $(NAME) $(OBJS_BONUS)

clean:
	@rm -rf $(OBJS) $(OBJS_BONUS)
	
fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY: all re clean fclean bonus

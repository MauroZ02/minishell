# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzangaro <mzangaro@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/12 15:07:53 by mzangaro          #+#    #+#              #
#    Updated: 2025/11/13 16:58:40 by mzangaro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

DEPENDENCIES = -lreadline

$(LIBFT):
		$(MAKE) -C $(LIBFT_PATH)

all: $(NAME)

SRCS = minishell.c

OBJS = $(SRCS:.c=.o)

HEADER = minishell.h

CC = cc
CFLAGS = -Wall -Wextra -Werror
$(NAME): $(OBJS) $(LIBFT) $(HEADER)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(DEPENDENCIES)

%.o: %.c $(HEADER)
		$(CC) $(CFLAGS) -c $< -o $@ 

RM = rm -f
clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all
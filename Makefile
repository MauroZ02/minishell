# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzangaro <mzangaro@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/12 15:07:53 by mzangaro          #+#    #+#              #
#    Updated: 2025/11/17 18:14:04 by mzangaro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
DEPENDENCIES = -lreadline

SRCS = minishell.c

HEADER = minishell.h

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(HEADER)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(DEPENDENCIES)

$(LIBFT):
		$(MAKE) -C $(LIBFT_PATH)

%.o: %.c $(HEADER)
		$(CC) $(CFLAGS) -c $< -o $@ 

RM = rm -f

clean:
		$(RM) $(OBJS) 
		$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
		$(RM) $(NAME) 
		$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all
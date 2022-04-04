# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/24 19:45:47 by nprimo            #+#    #+#              #
#    Updated: 2022/03/09 11:48:26 by nprimo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

LIBFT = libft/libft.a
LIBS = -lreadline $(LIBFT) 

SRC = src
OBJ = obj
INC = inc
SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

NAME = minishell

$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(OBJ)
	@make -C libft/ 
	$(CC) $(CFLAGS) $(LIBS) -I $(INC) -c $< -o $@

.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(wildcard $(OBJ)/*.o)

fclean: clean
	$(RM) $(NAME)

re: fclean all

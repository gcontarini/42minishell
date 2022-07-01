# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nprimo <nprimo@student.42lisboa.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/24 19:45:47 by nprimo            #+#    #+#              #
#    Updated: 2022/07/01 12:56:23 by nprimo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COMPILER
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
RM = rm -rf

# FILES
SRC = src
OBJ = obj
INC = inc
SRCS = $(wildcard $(SRC)/*/*.c)
OBJS = $(patsubst %.c, $(OBJ)/%.o, $(notdir $(SRCS)))
SRCS_TEST := $(shell find $(SRC)/*/*.c | grep -v main.c)
SRCS_TEST += $(wildcard test/*.c)
LIBFT = libft/libft.a

# LINKER
LIBS = -lreadline $(LIBFT) 

# TARGET
NAME = minishell

# RULES
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -I $(INC) $^ -o $@ $(LIBS) 

$(OBJ)/%.o: $(SRC)/*/%.c
	@mkdir -p $(OBJ)
	@make -C libft/ 
	$(CC) $(CFLAGS) -I $(INC) -c $< -o $@

tester: $(SRCS_TEST)
	$(CC) -Wall -g -fsanitize=address -I $(INC) $^ $(LIBS) 

clean:
	$(RM) $(wildcard $(OBJ)/*.o)

fclean: clean
	$(RM) $(NAME)
	@make fclean -C libft/

re: fclean all

.PHONY: all, clean, fclean, re
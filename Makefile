# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gcontari <gcontari@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/24 19:45:47 by nprimo            #+#    #+#              #
#    Updated: 2022/04/05 11:17:02 by gcontari         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COMPILER
CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

# FILES
SRC = src
OBJ = obj
INC = inc
SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
LIBFT = libft/libft.a

# LINKER
LIBS = -lreadline $(LIBFT) 

# TARGET
NAME = minishell

# RULES
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) -I $(INC) $^ -o $@ 

$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(OBJ)
	@make -C libft/ 
	$(CC) $(CFLAGS) -I $(INC) -c $< -o $@

clean:
	$(RM) $(wildcard $(OBJ)/*.o)

fclean: clean
	$(RM) $(NAME)
	@make fclean -C libft/

re: fclean all

.PHONY: all, clean, fclean, re
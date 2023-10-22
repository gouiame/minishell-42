# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgouiame <cgouiame@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/27 14:24:27 by cgouiame          #+#    #+#              #
#    Updated: 2023/10/22 17:52:26 by cgouiame         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
INCLUDE = minishell.h
CC = cc
READLINE = $(shell brew --prefix readline)
FLAGS = -Wall -Werror -Wextra  -I$(READLINE)/include #-fsanitize=address -g
FILES = env.c token.c utils.c error.c main.c utils2.c utils_token.c \
		expand.c redirections.c heredoc.c utils_token2.c parsing.c signal.c\
		parsing2.c export.c get_env.c echo.c unset.c execution.c ft_cd.c \
		ft_pwd.c ft_exit.c free.c utils_ex.c utils_exec.c utils_exp.c utils3.c \
		utils4.c parsing3.c
		
OBJ= $(FILES:.c=.o)

all : $(NAME)

$(NAME): $(OBJ) $(INCLUDE)
		 		$(CC) $(OBJ) $(FLAGS) -lreadline -L$(READLINE)/lib -o $(NAME)

%.o : %.c $(INCLUDE)
		$(CC) $(FLAGS) -c $< 

clean :
		 rm -f $(OBJ)

fclean : clean
		 rm -f $(NAME)

re : fclean all
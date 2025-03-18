# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: motelti <motelti@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/03 17:18:40 by motelti           #+#    #+#              #
#    Updated: 2025/03/18 15:17:40 by motelti          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
CFLAGS	= -Wall -Werror -Wextra
RM		= @rm -f


NAME	= pipex
HEADER = pipex.h

SRC		= ft_pipex/pipex_utils.c \
		  ft_pipex/pipex.c \
          $(addprefix ./ft_pipex/, $(LIBFT_SRC)) 

OBJ		= $(SRC:.c=.o)


LIBFT_SRC = ft_bzero.c ft_calloc.c \
    ft_putchar_fd.c ft_putstr_fd.c ft_split.c \
    ft_strdup.c ft_strlen.c ft_strncmp.c \
    ft_substr.c ft_memset.c ft_strnstr.c ft_strjoin.c

all: $(NAME)  clean


%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -MMD


$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ) $(BONUS_OBJ) $(OBJ:.o=.d)

fclean: clean
	$(RM) $(NAME)

re: fclean all

-include $(OBJ:.o=.d)
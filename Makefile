# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/06 17:15:27 by yonghyle          #+#    #+#              #
#    Updated: 2023/02/06 18:58:46 by yonghyle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -Iincludes -lft -Llibft

RM = rm -rf

LIBFT_A = libft/libft.a

NAME = push_swap

#-------------------------------------------

MANDATORY_SRCS := $(wildcard srcs/*.c)
#MANDATORY_SRCS = $(addprefix srcs/,)
MANDATORY_OBJS = $(MANDATORY_SRCS:.c=.o)

#-------------------------------------------

BONUS_SRCS = srcs/*_bonus.c
#BONUS_SRCS = $(addprefix srcs/,)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

#-------------------------------------------

all: $(NAME)

$(NAME): make_mandatory

make_mandatory: $(MANDATORY_OBJS)
		make -C libft
		$(CC) -o $(NAME) $(CFLAGS) $(MANDATORY_OBJS)
		touch $@

bonus: make_bonus

make_bonus: $(BONUS_OBJS)
		make -C libft
		$(CC) -o $(NAME) $(CFLAGS) $(BONUS_OBJS)
		touch $@

clean:
		cd libft; make clean
		$(RM) ${MANDATORY_OBJS} ${BONUS_OBJS} make_mandatory make_bonus

fclean:
		cd libft; make fclean
		make clean
		$(RM) $(NAME)

re:
		make fclean
		make all
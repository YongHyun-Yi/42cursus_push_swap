# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/06 17:15:27 by yonghyle          #+#    #+#              #
#    Updated: 2023/02/07 11:16:02 by yonghyle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibft/includes

RM = rm -rf

LIBFT_A = libft/libft.a

NAME = push_swap

#-------------------------------------------

# MANDATORY_SRCS = $(addprefix srcs/, $(wildcard *.c))
MANDATORY_SRCS = $(addprefix srcs/,\
							 my_instructions.c \
							 push_instructions.c \
							 push_swap.c \
							 rotate_instructions.c \
							 swap_instructions.c \
)
MANDATORY_OBJS = $(MANDATORY_SRCS:.c=.o)

#-------------------------------------------

BONUS_SRCS = $(addprefix srcs/, $(wildcard *_bonus.c))
#BONUS_SRCS = $(addprefix srcs/,)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

#-------------------------------------------

all: $(NAME)

$(NAME): $(MANDATORY_OBJS)
		make -C libft
		$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_A)

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
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/06 17:15:27 by yonghyle          #+#    #+#              #
#    Updated: 2023/02/08 14:46:27 by yonghyle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibft/includes

RM = rm -rf

LIBFT_A = libft/libft.a

NAME = push_swap

BONUS_NAME = checker

#-------------------------------------------

MANDATORY_SRCS = $(wildcard srcs/*.c)
# MANDATORY_SRCS = $(addprefix srcs/,)
MANDATORY_OBJS = $(MANDATORY_SRCS:.c=.o)

#-------------------------------------------

BONUS_SRCS = $(wildcard bonus_srcs/*.c)
#BONUS_SRCS = $(addprefix bonus_srcs/,)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

#-------------------------------------------

all: $(NAME)

$(NAME): $(MANDATORY_OBJS)
		make -C libft
		$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_A)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)
		make -C libft
		$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_A)

clean:
		cd libft; make clean
		$(RM) ${MANDATORY_OBJS} ${BONUS_OBJS}

fclean:
		cd libft; make fclean
		make clean
		$(RM) $(NAME) $(BONUS_NAME)

re:
		make fclean
		make all
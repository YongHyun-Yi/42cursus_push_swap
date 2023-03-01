# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/06 17:15:27 by yonghyle          #+#    #+#              #
#    Updated: 2023/03/02 05:19:59 by yonghyle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibft/includes

RM = rm -rf

LIBFT_A = libft/libft.a

NAME = push_swap

BONUS_NAME = checker

#-------------------------------------------

MANDATORY_SRCS = $(addprefix srcs/, \
cir_dlst_utils.c                instruction_utils.c             my_push_swap_solve2.c           rotate_instructions.c \
cmp_utils.c                     lis_utils.c                     push_instructions.c             rotcnt_utils.c \
etc_utils.c                     my_instructions.c               push_swap.c                     swap_instructions.c \
get_node_utils.c                my_push_swap_solve.c            reverse_rotate_instructions.c \
)
MANDATORY_OBJS = $(MANDATORY_SRCS:.c=.o)

#-------------------------------------------

BONUS_SRCS = $(addprefix bonus_srcs/,\
cir_dlst_utils_bonus.c                  my_instructions_bonus.c                 push_swap_bonus.c                       rotate_instructions_bonus.c \
etc_utils_bonus.c                       push_instructions_bonus.c               reverse_rotate_instructions_bonus.c     swap_instructions_bonus.c \
)
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
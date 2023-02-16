/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:48:24 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/16 14:27:23 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

# define SUCCESS 1
# define FAIL 0

typedef struct s_dlist
{
	int				value;
	struct s_dlist	*prev;
	struct s_dlist	*next;
}	t_dlist;

typedef struct s_ps_stat
{
	t_dlist	*stack_a;
	t_dlist	*stack_b;
}	t_ps_stat;

void	my_swap(t_dlist *my_stack);
void	my_push(t_dlist *dest, t_dlist *src);
void	my_rotate(t_dlist **my_stack);
void	my_reverse_rotate(t_dlist **my_stack);

void	ft_cir_dlstadd_back(t_dlist **lst, t_dlist *new);
void	ft_cir_dlstadd_front(t_dlist **lst, t_dlist *new);

#endif
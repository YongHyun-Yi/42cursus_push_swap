/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 00:12:48 by yonghyle          #+#    #+#             */
/*   Updated: 2023/03/02 00:13:05 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_BONUS_H
# define PUSH_SWAP_BONUS_H

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
	char	*bit_array;
	char	**split_argv;
	t_dlist	*stack_a;
	t_dlist	*stack_b;
}	t_ps_stat;

void	my_swap(t_dlist *my_stack);
t_dlist	*my_pop(t_dlist **my_stack);
void	my_push(t_dlist **dest, t_dlist **src);
void	my_rotate(t_dlist **my_stack);
void	my_reverse_rotate(t_dlist **my_stack);

void	sa(t_ps_stat *ps_stat);
void	sb(t_ps_stat *ps_stat);
void	ss(t_ps_stat *ps_stat);

void	pa(t_ps_stat *ps_stat);
void	pb(t_ps_stat *ps_stat);

void	ra(t_ps_stat *ps_stat);
void	rb(t_ps_stat *ps_stat);
void	rr(t_ps_stat *ps_stat);

void	rra(t_ps_stat *ps_stat);
void	rrb(t_ps_stat *ps_stat);
void	rrr(t_ps_stat *ps_stat);

t_dlist	*ft_dlstnew(int value);
void	ft_cir_dlstadd_back(t_dlist **lst, t_dlist *new);
void	ft_cir_dlstadd_front(t_dlist **lst, t_dlist *new);
size_t	ft_cir_dlstsize(t_dlist *lst);
int		ft_cir_dlst_hasval(t_dlist *my_dlst, int val);
void	ft_cir_dlstclear(t_dlist **my_dlst);
int		ft_value_cmp(t_dlist *a, t_dlist *b);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:48:24 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/20 18:01:13 by yonghyle         ###   ########.fr       */
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
	size_t	com_cnt;
}	t_ps_stat;

void	my_swap(t_dlist *my_stack);
void	my_push(t_dlist **dest, t_dlist **src);
void	my_rotate(t_dlist **my_stack);
void	my_reverse_rotate(t_dlist **my_stack);

void	sa(t_ps_stat *ps_stat);
void	pa(t_ps_stat *ps_stat);
void	ra(t_ps_stat *ps_stat);
void	rra(t_ps_stat *ps_stat);
void	n_rot_a(t_ps_stat *ps_stat, int rot_cnt);
void	sb(t_ps_stat *ps_stat);
void	pb(t_ps_stat *ps_stat);
void	rb(t_ps_stat *ps_stat);
void	rrb(t_ps_stat *ps_stat);
void	n_rot_b(t_ps_stat *ps_stat, int rot_cnt);
void	ss(t_ps_stat *ps_stat);
void	rr(t_ps_stat *ps_stat);
void	rrr(t_ps_stat *ps_stat);

void	ft_cir_dlstadd_back(t_dlist **lst, t_dlist *new);
void	ft_cir_dlstadd_front(t_dlist **lst, t_dlist *new);
size_t	ft_cir_dlstsize(t_dlist *lst);

void	print_my_stack(t_dlist *my_stack);
void	print_all_my_stack(t_ps_stat *ps_stat); // 디버깅용

int 	ft_is_stack_sorted(t_dlist *my_stack);
int		ft_is_allstack_sorted(t_ps_stat *ps_stat);

void	sort_under5_elements(t_ps_stat *ps_stat);
void	sort_3_elements(t_ps_stat *ps_stat);
int		my_push_swap_solve(t_ps_stat *ps_stat);

#endif
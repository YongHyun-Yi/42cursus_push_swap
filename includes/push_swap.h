/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:48:24 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/24 14:12:48 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

#include <stdio.h>

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
	t_list	*inst_lst;
}	t_ps_stat;

void	my_swap(t_dlist *my_stack);
t_dlist	*my_pop(t_dlist **my_stack);
void	my_push(t_dlist **dest, t_dlist **src);
void	my_rotate(t_dlist **my_stack);
void	my_reverse_rotate(t_dlist **my_stack);
int		my_add_inst(t_list **inst_lst, char *str);

void	sa(t_ps_stat *ps_stat);
void	pa(t_ps_stat *ps_stat);
void	ra(t_ps_stat *ps_stat);
void	rra(t_ps_stat *ps_stat);
void	n_ra(t_ps_stat *ps_stat, long long cnt);
void	sb(t_ps_stat *ps_stat);
void	pb(t_ps_stat *ps_stat);
void	rb(t_ps_stat *ps_stat);
void	rrb(t_ps_stat *ps_stat);
void	n_rb(t_ps_stat *ps_stat, long long cnt);
void	ss(t_ps_stat *ps_stat);
void	rr(t_ps_stat *ps_stat);
void	rrr(t_ps_stat *ps_stat);
void	n_rr(t_ps_stat *ps_stat, long long cnt);

t_dlist *ft_dlstnew(int value);
void	ft_cir_dlstadd_back(t_dlist **lst, t_dlist *new);
void	ft_cir_dlstadd_front(t_dlist **lst, t_dlist *new);
size_t	ft_cir_dlstsize(t_dlist *lst);

size_t	my_abs(long long nb);

int		dlist_valcmp(t_dlist *a, t_dlist *b);
t_dlist	*get_largest_node(t_dlist *my_stack);
t_dlist	*get_smallest_node(t_dlist *my_stack);

int 	dlist_rotcmp(t_dlist *dest, t_dlist *src, t_dlist *a, t_dlist *b);
t_dlist	*get_leastrot_node(t_dlist *dest, t_dlist *src);

long long	get_rotcnt_totop(t_dlist *my_stack, t_dlist *target_node);
long long	get_rotcnt_topos(t_dlist *my_stack, t_dlist *target_node);
long long	get_double_rotcnt(t_dlist *dest, t_dlist *src, t_dlist *target_node);
size_t	get_total_rotcnt(t_dlist *dest, t_dlist *src, t_dlist *target_node);

void	print_my_stack(t_dlist *my_stack);
void	print_all_my_stack(t_ps_stat *ps_stat); // 디버깅용

int 	ft_is_stack_sorted(t_dlist *my_stack);
int		ft_is_allstack_sorted(t_ps_stat *ps_stat);

void	sort_under5_elements(t_ps_stat *ps_stat);
void	sort_3_elements(t_ps_stat *ps_stat);
int		my_push_swap_solve(t_ps_stat *ps_stat);
void	sort_under100_elements(t_ps_stat *ps_stat);

#endif
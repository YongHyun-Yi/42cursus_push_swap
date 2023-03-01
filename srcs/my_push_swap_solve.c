/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_push_swap_solve.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:34:21 by yonghyle          #+#    #+#             */
/*   Updated: 2023/03/01 18:18:42 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

size_t	my_abs(long long nb)
{
	if (nb < 0)
		nb *= -1;
	return (nb);
}

void	greedy_b_to_a(t_ps_stat *ps_stat)
{
	t_dlist *cur_node;

	cur_node = get_leastrot_node(ps_stat->stack_a, ps_stat->stack_b);
	n_rr(ps_stat, get_double_rotcnt(ps_stat->stack_a, ps_stat->stack_b, cur_node));
	n_ra(ps_stat, get_rotcnt_topos(ps_stat->stack_a, cur_node));
	n_rb(ps_stat, get_rotcnt_totop(ps_stat->stack_b, cur_node));
	pa(ps_stat);
}

void	sort_under5_elements(t_ps_stat *ps_stat)
{
	int		cnt;

	cnt = (int)ft_cir_dlstsize(ps_stat->stack_a) - 3;
	while (ft_cir_dlstsize(ps_stat->stack_a) > 3)
		pb(ps_stat);
	if (!ft_is_stack_sorted(ps_stat->stack_a))
		sort_3_elements(ps_stat);
	while (cnt--)
		greedy_b_to_a(ps_stat);
	n_ra(ps_stat, get_rotcnt_totop(ps_stat->stack_a, get_smallest_node(ps_stat->stack_a)));
	return ;
}

void	sort_3_elements(t_ps_stat *ps_stat)
{
	t_dlist *	first;
	t_dlist *	second;
	t_dlist *	third;

	first = ps_stat->stack_a;
	second = first->next;
	third = second->next;
	if (ft_value_cmp(first, second) && !ft_value_cmp(second, third))
	{
		rra(ps_stat);
		if (!ft_value_cmp(third, first))
			sa(ps_stat);
	}
	else if (ft_value_cmp(second, third) && ft_value_cmp(third, first))
		ra(ps_stat);
	else
	{
		sa(ps_stat);
		if (!ft_value_cmp(second, third) && ft_value_cmp(third, first))
			rra(ps_stat);
	}
	return ;
}

void	my_push_swap_solve(t_ps_stat *ps_stat)
{
	size_t lst_size;

	lst_size = ft_cir_dlstsize(ps_stat->stack_a);
	if (lst_size == 2)
		sa(ps_stat);
	else if (lst_size == 3)
		sort_3_elements(ps_stat);
	else if (lst_size <= 5)
		sort_under5_elements(ps_stat);
	else
		sort_over_elements(ps_stat);
}
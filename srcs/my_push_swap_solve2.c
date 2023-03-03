/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_push_swap_solve2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 09:46:54 by yonghyle          #+#    #+#             */
/*   Updated: 2023/03/01 23:59:49 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	my_bubble_sort(t_dlist *my_dlist)
{
	t_dlist	*cur_node;

	cur_node = my_dlist;
	while (!ft_is_stack_sorted(my_dlist))
	{
		if (cur_node->next != my_dlist
			&& !ft_value_cmp(cur_node, cur_node->next))
			my_swap(cur_node);
		cur_node = cur_node->next;
	}
}

int	get_pivot(t_dlist *my_stack, t_dlist *lis_list, int *pivot)
{
	t_dlist	*nonlis_list;
	t_dlist	*cur_node;
	size_t	center_idx;

	nonlis_list = get_nonlis_list(my_stack, lis_list);
	if (!nonlis_list)
		return (FAIL);
	my_bubble_sort(nonlis_list);
	cur_node = nonlis_list;
	center_idx = ft_cir_dlstsize(nonlis_list) / 2;
	while (center_idx--)
		cur_node = cur_node->next;
	*pivot = cur_node->value;
	ft_cir_dlstclear(&nonlis_list);
	return (SUCCESS);
}

static void	a_to_b(t_ps_stat *ps_stat, t_dlist *lis_list, int pivot)
{
	size_t	max_i;

	if (ft_cir_dlstsize(lis_list) < 5)
		sort_under5_elements(ps_stat);
	else
	{
		max_i = ft_cir_dlstsize(ps_stat->stack_a);
		while (max_i--)
		{
			if (ft_cir_dlst_hasval(lis_list, (ps_stat->stack_a)->value))
				ra(ps_stat);
			else
			{
				pb(ps_stat);
				if (ft_cir_dlstsize(ps_stat->stack_b) > 1
					&& (ps_stat->stack_b)->value >= pivot
					&& ((ps_stat->stack_b)->next)->value < pivot)
					rb(ps_stat);
			}
		}
	}
	ft_cir_dlstclear(&lis_list);
}

void	sort_over_elements(t_ps_stat *ps_stat)
{
	t_dlist	*lis_list;
	t_dlist	*lis_idx_list;
	int		pivot;

	lis_idx_list = get_lis_idx_list(ps_stat->stack_a);
	if (!lis_idx_list)
		my_exit(ps_stat, FAIL);
	lis_list = get_lis_list(ps_stat->stack_a, lis_idx_list);
	ft_cir_dlstclear(&lis_idx_list);
	if (!lis_list)
		my_exit(ps_stat, FAIL);
	if (!get_pivot(ps_stat->stack_a, lis_list, &pivot))
		my_exit(ps_stat, FAIL);
	a_to_b(ps_stat, lis_list, pivot);
	while (ps_stat->stack_b)
		greedy_b_to_a(ps_stat);
	n_ra(ps_stat, get_rotcnt_totop(ps_stat->stack_a,
			get_smallest_node(ps_stat->stack_a)));
	return ;
}

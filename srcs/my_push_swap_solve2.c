/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_push_swap_solve2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 09:46:54 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/27 18:36:40 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	inst_lst_optimizing(t_list *inst_lst)
{
	// ra - rra(둘 다 삭제), rb(rr), rrr(rrb)
	// rra - ra(둘 다 삭제), rrb(rrr), rr(rb)
	// rb - rrb(둘 다 삭제), ra(rr), rrr(rra)
	// rrb - rb(둘 다 삭제), rra(rrr), rr(ra)
	// rr - rra(rb), rrb(ra)
	// rrr - ra(rrb), rb(rra)
	// sa - sb(ss)
	// sb - sa(ss)

	t_list *cur_node;
	t_list *cmp_node;
	char *cur_inst;
	char *cmp_inst;

	cur_node = inst_lst;
	cur_inst = (char *)(cur_node->content);
	while (cur_node->next)
	{
		cmp_node = cur_node->next;
		while(cmp_node)
		{
			cmp_inst = (char *)(cmp_node->content);
			if (cur_inst[0] != cmp_inst[0] || (cur_inst[0] == 'p' || cmp_inst[0] == 'p'))
				break ;
			// 전혀 다른종류의 명령어이거나 or push 명령어이거나

			if (cur_inst[0] == 's' && (!ft_strnstr(cur_inst, "ss", 3) && !ft_strnstr(cmp_inst, "ss", 3)) && cur_inst[1] != cmp_inst[1]) // sa sb
			{
				cur_node->content = "ss\n";
				cmp_node->content = "";
				break ;
			}
			else // r? r?
			{
				if ((ft_strnstr(cur_inst, "ra\n", 3) && ft_strnstr(cmp_inst, "rb\n", 3)) || (ft_strnstr(cur_inst, "rb\n", 3) && ft_strnstr(cmp_inst, "ra\n", 3)))
				{
					cur_node->content = "rr\n";
					cmp_node->content = "";
					break ;
				}
				if ((ft_strnstr(cur_inst, "rra", 3) && ft_strnstr(cmp_inst, "rrb", 3)) || (ft_strnstr(cur_inst, "rrb", 3) && ft_strnstr(cmp_inst, "rra", 3)))
				{
					cur_node->content = "rrr\n";
					cmp_node->content = "";
					break ;
				}
				if ((ft_strnstr(cur_inst, "rr\n", 3) && ft_strnstr(cmp_inst, "rra", 3)) || (ft_strnstr(cur_inst, "rra", 3) && ft_strnstr(cmp_inst, "rr\n", 3)))
				{
					cur_node->content = "rb\n";
					cmp_node->content = "";
					break ;
				}
				if ((ft_strnstr(cur_inst, "rr\n", 3) && ft_strnstr(cmp_inst, "rrb", 3)) || (ft_strnstr(cur_inst, "rrb", 3) && ft_strnstr(cmp_inst, "rr\n", 3)))
				{
					cur_node->content = "ra\n";
					cmp_node->content = "";
					break ;
				}
				if ((ft_strnstr(cur_inst, "rrr", 3) && ft_strnstr(cmp_inst, "ra\n", 3)) || (ft_strnstr(cur_inst, "ra\n", 3) && ft_strnstr(cmp_inst, "rrr", 3)))
				{
					cur_node->content = "rrb\n";
					cmp_node->content = "";
					break ;
				}
				if ((ft_strnstr(cur_inst, "rrr", 3) && ft_strnstr(cmp_inst, "rb\n", 3)) || (ft_strnstr(cur_inst, "rb\n", 3) && ft_strnstr(cmp_inst, "rrr", 3)))
				{
					cur_node->content = "rra\n";
					cmp_node->content = "";
					break ;
				}
			}
			cmp_node = cmp_node->next;
		}
		cur_node = cur_node->next;
		cur_inst = (char *)(cur_node->content);
	}
	return ;
}

// --------------------------------------------------------------------------------------------

int	get_pivot(t_dlist *my_stack)
{
	int min_val;
	int max_val;

	min_val = get_smallest_node(my_stack)->value;
	max_val = get_largest_node(my_stack)->value;
	return ((min_val + max_val) / 2);
	
	// 좀 더 디테일하게 다듬을것...
}

// --------------------------------------------------------------------------------------------

void	a_to_b(t_ps_stat *ps_stat, t_dlist *lis_list, int pivot) // static function
{
	size_t max_i;

	if (ft_cir_dlstsize(lis_list) < 5)
	{
		sort_under5_elements(ps_stat);
		return ;
	}
	max_i = ft_cir_dlstsize(ps_stat->stack_a);
	while(max_i--)
	{
		if (ft_cir_dlst_hasval(lis_list, (ps_stat->stack_a)->value))
			ra(ps_stat);
		else
		{
			pb(ps_stat);
			if (ft_cir_dlstsize(ps_stat->stack_b) > 1 && (ps_stat->stack_b)->value >= pivot && ((ps_stat->stack_b)->next)->value < pivot)
				rb(ps_stat);
		}
	}
}

void	sort_over_elements(t_ps_stat *ps_stat)
{
	t_dlist *lis_list;
	int	pivot;

	lis_list = get_lis_list(ps_stat->stack_a);
	pivot = get_pivot(ps_stat->stack_a);

	a_to_b(ps_stat, lis_list, pivot);
	while (ps_stat->stack_b)
		greedy_b_to_a(ps_stat);
	n_ra(ps_stat, get_rotcnt_totop(ps_stat->stack_a, get_smallest_node(ps_stat->stack_a)));

	return ;
}

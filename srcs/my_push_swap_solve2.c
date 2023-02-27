/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_push_swap_solve2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 09:46:54 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/27 16:49:48 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// get biggest sorted
// bubble sort or quick sort
// divide 2 group
// divide 3 group <- 그냥 인자 갯수에 따라 청크 갯수를 나눠주는식으로 해도 될듯...?

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

int	ft_cir_dlst_hasval(t_dlist *my_dlst, int val)
{
	t_dlist	*cur_node;

	if (!my_dlst)
		return (0);
	cur_node = my_dlst;
	while (1)
	{
		if (cur_node->value == val)
			return (1);
		if (cur_node->next == my_dlst)
			return (0);
		cur_node = cur_node->next;
	}
}

// --------------------------------------------------------------------------------------------

size_t get_lis_idx(t_dlist *target_node, t_dlist *idx_lst)
{
	size_t	cur_idx;
	t_dlist	*val_cmp_node;
	t_dlist	*idx_cmp_node;

	if (idx_lst == NULL)
		return (1);
	cur_idx = get_largest_node(idx_lst)->value;
	val_cmp_node = target_node->prev;
	idx_cmp_node = idx_lst->prev;
	while (1)
	{
		if (cur_idx == (size_t)idx_cmp_node->value)
		{
			if (target_node->value > val_cmp_node->value)
				return (cur_idx + 1);
			if (cur_idx == 1)
				return (1);
			cur_idx--;
		}
		val_cmp_node = val_cmp_node->prev;
		idx_cmp_node = idx_cmp_node->prev;
	}
}

t_dlist *get_lis_idx_list(t_dlist *my_stack)
{
	t_dlist *idx_list;
	t_dlist *cur_node;
	t_dlist *new;

	idx_list = NULL;
	cur_node = my_stack;
	while (1)
	{
		new = ft_dlstnew(get_lis_idx(cur_node, idx_list));
		if (!new)
			return (FAIL);
		ft_cir_dlstadd_back(&idx_list, new);
		if (cur_node->next == my_stack)
			break ;
		cur_node = cur_node->next;
	}
	return (idx_list);
}

t_dlist *get_lis_list(t_dlist *my_stack)
{
	t_dlist *idx_list;
	t_dlist *lis_list;
	size_t	cur_idx;
	t_dlist *cur_node;
	t_dlist *new;

	idx_list = get_lis_idx_list(my_stack);
	lis_list = NULL;
	cur_idx = get_largest_node(idx_list)->value;
	cur_node = my_stack->prev;
	idx_list = idx_list->prev;
	while (1)
	{
		if ((size_t)idx_list->value == cur_idx)
		{
			new = ft_dlstnew(cur_node->value);
			if (!new)
				return (FAIL);
			ft_cir_dlstadd_back(&lis_list, new);
			cur_idx--;
		}
		if (cur_node->prev == my_stack->prev)
			break ;
		cur_node = cur_node->prev;
		idx_list = idx_list->prev;
	}
	return (lis_list);
}

// --------------------------------------------------------------------------------------------

void	b_to_a(t_ps_stat *ps_stat)
{
	t_dlist *target_node;

	while (ps_stat->stack_b)
	{
		target_node = get_leastrot_node(ps_stat->stack_a, ps_stat->stack_b);
		n_rr(ps_stat, get_double_rotcnt(ps_stat->stack_a, ps_stat->stack_b, target_node));
		n_ra(ps_stat, get_rotcnt_topos(ps_stat->stack_a, target_node));
		n_rb(ps_stat, get_rotcnt_totop(ps_stat->stack_b, target_node));
		pa(ps_stat);
	}
}

void	a_to_b(t_ps_stat *ps_stat, t_dlist *lis_list, int pivot)
{
	size_t max_i;

	if (ft_cir_dlstsize(lis_list) < 3)
	{
		while (ft_cir_dlstsize(ps_stat->stack_a) > 3)
		{
			pb(ps_stat);
			if (ft_cir_dlstsize(ps_stat->stack_b) > 1 && (ps_stat->stack_b)->value >= pivot && ((ps_stat->stack_b)->next)->value < pivot)
				rb(ps_stat);
		}
		sort_3_elements(ps_stat);
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
	return ;
	// 그리디가 항상 최선은 아니라는것을 생각해야한다
	// 오히려 모두 순회하는편이 더 적게 먹힌다...
	//
	// LIS 의 사이즈가 3보다 작다면 -> 3개만 남겨놓고 모두 b로 보낸다, a는 sort 3로 정렬
	// 그렇지 않으면 -> LIS에 없는 애들 전부 b로 보내고 a는 ra로 정렬되어있는 애들만 남아있는 상태
}

int	get_pivot(t_dlist *my_stack)
{
	int min_val;
	int max_val;

	min_val = get_smallest_node(my_stack)->value;
	max_val = get_largest_node(my_stack)->value;
	return ((min_val + max_val) / 2);
	
	// 좀 더 디테일하게 다듬을것...
}

void	sort_under100_elements(t_ps_stat *ps_stat)
{
	t_dlist *lis_list;
	int	pivot;

	lis_list = get_lis_list(ps_stat->stack_a);
	pivot = get_pivot(ps_stat->stack_a);

	a_to_b(ps_stat, lis_list, pivot);
	b_to_a(ps_stat);
	n_ra(ps_stat, get_rotcnt_totop(ps_stat->stack_a, get_smallest_node(ps_stat->stack_a)));

	return ;
}

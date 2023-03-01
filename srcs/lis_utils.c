/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:22:10 by yonghyle          #+#    #+#             */
/*   Updated: 2023/03/01 18:25:47 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_dlist *get_nonlis_list(t_dlist *my_stack, t_dlist *lis_list)
{
	t_dlist *nonlis_list;
	t_dlist *iter;
	t_dlist *new;

	nonlis_list = NULL;
	iter = my_stack;
	while (1)
	{
		if (!ft_cir_dlst_hasval(lis_list, iter->value))
		{
			new = ft_dlstnew(iter->value);
			if (!new)
			{
				ft_cir_dlstclear(&nonlis_list);
				return (FAIL);
			}
			ft_cir_dlstadd_back(&nonlis_list, new);
		}
		if (iter->next == my_stack)
			break ;
		iter = iter->next;
	}
	return (nonlis_list);
}

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
		{
			ft_cir_dlstclear(&idx_list);
			return (FAIL);
		}
		ft_cir_dlstadd_back(&idx_list, new);
		if (cur_node->next == my_stack)
			break ;
		cur_node = cur_node->next;
	}
	return (idx_list);
}

t_dlist *get_lis_list(t_dlist *my_stack, t_dlist *lis_idx_list)
{
	t_dlist *lis_list;
	size_t	cur_idx;
	t_dlist *cur_node;
	t_dlist *new;

	lis_list = NULL;
	cur_idx = (size_t)(get_largest_node(lis_idx_list)->value);
	cur_node = my_stack;
	while (cur_idx)
	{
		cur_node = cur_node->prev;
		lis_idx_list = lis_idx_list->prev;
		if ((size_t)lis_idx_list->value == cur_idx)
		{
			new = ft_dlstnew(cur_node->value);
			if (!new)
			{
				ft_cir_dlstclear(&lis_list);
				return (FAIL);
			}
			ft_cir_dlstadd_back(&lis_list, new);
			cur_idx--;
		}
	}
	return (lis_list);
}
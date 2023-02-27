/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:22:10 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/27 18:22:30 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
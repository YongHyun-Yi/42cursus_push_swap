/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_node_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:41:32 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/27 17:42:03 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_dlist *get_largest_node(t_dlist *my_stack)
{
	t_dlist *cur_node;
	t_dlist *max_node;

	cur_node = my_stack;
	max_node = cur_node;
	while (cur_node->next != my_stack)
	{
		cur_node = cur_node->next;
		if (!ft_value_cmp(cur_node, max_node))
			max_node = cur_node;
	}
	return (max_node);
}

t_dlist *get_smallest_node(t_dlist *my_stack)
{
	t_dlist *cur_node;
	t_dlist *min_node;

	cur_node = my_stack;
	min_node = cur_node;
	while (cur_node->next != my_stack)
	{
		cur_node = cur_node->next;
		if (ft_value_cmp(cur_node, min_node))
			min_node = cur_node;
	}
	return (min_node);
}

t_dlist *get_leastrot_node(t_dlist *dest, t_dlist *src)
{
	t_dlist *cur_node;
	t_dlist *least_node;

	cur_node = src;
	least_node = NULL;
	while (1)
	{
		if (least_node == NULL)
			least_node = cur_node;
		else if (ft_total_rotcnt_cmp(dest, src, cur_node, least_node))
			least_node = cur_node;
		if (cur_node->next == src)
			break ;
		cur_node = cur_node->next;
	}
	return (least_node);
}

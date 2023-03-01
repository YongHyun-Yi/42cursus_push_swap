/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 00:20:31 by yonghyle          #+#    #+#             */
/*   Updated: 2023/03/02 00:23:16 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_value_cmp(t_dlist *a, t_dlist *b)
{
	return (a->value < b->value);
}

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

void	my_exit(t_ps_stat *ps_stat, int no_err)
{
	if (ps_stat->bit_array)
	{
		free(ps_stat->bit_array);
		ps_stat->bit_array = NULL;
	}
	if (ps_stat->split_argv)
	{
		free(ps_stat->split_argv);
		ps_stat->split_argv = NULL;
	}
	if (ps_stat->stack_a)
		ft_cir_dlstclear(&ps_stat->stack_a);
	if (ps_stat->stack_b)
		ft_cir_dlstclear(&ps_stat->stack_b);
	if (no_err)
		exit(EXIT_SUCCESS);
	ft_putstr_fd("Error\n", 2);
	exit(EXIT_FAILURE);
}

int	ft_is_stack_sorted(t_dlist *my_stack)
{
	t_dlist	*cur_node;

	if (!my_stack)
		return (FAIL);
	cur_node = my_stack;
	while (cur_node->next != my_stack)
	{
		if (!ft_value_cmp(cur_node, cur_node->next))
			return (FAIL);
		cur_node = cur_node->next;
	}
	return (SUCCESS);
}

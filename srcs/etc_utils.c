/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 23:54:59 by yonghyle          #+#    #+#             */
/*   Updated: 2023/03/02 05:09:56 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	my_exit(t_ps_stat *ps_stat, int no_err)
{
	if (ps_stat->bit_array)
		free(ps_stat->bit_array);
	if (ps_stat->split_argv)
		free_splits(ps_stat->split_argv);
	if (ps_stat->stack_a)
		ft_cir_dlstclear(&ps_stat->stack_a);
	if (ps_stat->stack_b)
		ft_cir_dlstclear(&ps_stat->stack_b);
	if (ps_stat->inst_lst)
		ft_lstclear(&ps_stat->inst_lst, NULL);
	if (no_err)
		exit(EXIT_SUCCESS);
	ft_putstr_fd("Error\n", STDERR_FILENO);
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

size_t	my_abs(long long nb)
{
	if (nb < 0)
		nb *= -1;
	return (nb);
}

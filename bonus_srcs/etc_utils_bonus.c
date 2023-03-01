/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 00:20:31 by yonghyle          #+#    #+#             */
/*   Updated: 2023/03/02 04:49:53 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

int	ft_value_cmp(t_dlist *a, t_dlist *b)
{
	return (a->value < b->value);
}

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

void	set_ps_func_arr(void (*func_arr[])(t_ps_stat *))
{
	func_arr[0] = sa;
	func_arr[1] = sb;
	func_arr[2] = ss;
	func_arr[3] = pa;
	func_arr[4] = pb;
	func_arr[5] = ra;
	func_arr[6] = rb;
	func_arr[7] = rr;
	func_arr[8] = rra;
	func_arr[9] = rrb;
	func_arr[10] = rrr;
}

void	set_ps_str_arr(char *str_arr[])
{
	str_arr[0] = "sa\n";
	str_arr[1] = "sb\n";
	str_arr[2] = "ss\n";
	str_arr[3] = "pa\n";
	str_arr[4] = "pb\n";
	str_arr[5] = "ra\n";
	str_arr[6] = "rb\n";
	str_arr[7] = "rr\n";
	str_arr[8] = "rra\n";
	str_arr[9] = "rrb\n";
	str_arr[10] = "rrr\n";
}

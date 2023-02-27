/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate_instructions.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:58:30 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/27 16:58:36 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_ps_stat *ps_stat)
{
	my_reverse_rotate(&ps_stat->stack_a);
	my_add_inst(&ps_stat->inst_lst, "rra");
}

void	rrb(t_ps_stat *ps_stat)
{
	my_reverse_rotate(&ps_stat->stack_b);
	my_add_inst(&ps_stat->inst_lst, "rrb");
}

void	rrr(t_ps_stat *ps_stat)
{
	my_reverse_rotate(&ps_stat->stack_a);
	my_reverse_rotate(&ps_stat->stack_b);
	my_add_inst(&ps_stat->inst_lst, "rrr");
}

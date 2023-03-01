/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_instructions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:18:51 by yonghyle          #+#    #+#             */
/*   Updated: 2023/03/01 19:20:53 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_ps_stat *ps_stat)
{
	my_swap(ps_stat->stack_a);
	my_add_inst(&ps_stat->inst_lst, "sa\n");
}

void	sb(t_ps_stat *ps_stat)
{
	my_swap(ps_stat->stack_b);
	my_add_inst(&ps_stat->inst_lst, "sb\n");
}

void	ss(t_ps_stat *ps_stat)
{
	my_swap(ps_stat->stack_a);
	my_swap(ps_stat->stack_b);
	my_add_inst(&ps_stat->inst_lst, "ss\n");
}
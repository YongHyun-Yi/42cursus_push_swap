/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_instructions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:19:19 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/27 17:00:28 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(t_ps_stat *ps_stat)
{
	my_rotate(&ps_stat->stack_a);
	my_add_inst(&ps_stat->inst_lst, "ra\n");
}

void	rb(t_ps_stat *ps_stat)
{
	my_rotate(&ps_stat->stack_b);
	my_add_inst(&ps_stat->inst_lst, "rb\n");
}

void	rr(t_ps_stat *ps_stat)
{
	my_rotate(&ps_stat->stack_a);
	my_rotate(&ps_stat->stack_b);
	my_add_inst(&ps_stat->inst_lst, "rr\n");
}

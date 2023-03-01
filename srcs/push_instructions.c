/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_instructions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:19:23 by yonghyle          #+#    #+#             */
/*   Updated: 2023/03/01 23:59:55 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pa(t_ps_stat *ps_stat)
{
	my_push(&ps_stat->stack_a, &ps_stat->stack_b);
	my_add_inst(&ps_stat->inst_lst, "pa\n");
}

void	pb(t_ps_stat *ps_stat)
{
	my_push(&ps_stat->stack_b, &ps_stat->stack_a);
	my_add_inst(&ps_stat->inst_lst, "pb\n");
}

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

#include "push_swap_bonus.h"

void	ra(t_ps_stat *ps_stat)
{
	my_rotate(&ps_stat->stack_a);
}

void	rb(t_ps_stat *ps_stat)
{
	my_rotate(&ps_stat->stack_b);
}

void	rr(t_ps_stat *ps_stat)
{
	my_rotate(&ps_stat->stack_a);
	my_rotate(&ps_stat->stack_b);
}

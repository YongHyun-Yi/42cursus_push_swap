/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_instructions_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:18:51 by yonghyle          #+#    #+#             */
/*   Updated: 2023/03/02 00:21:40 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	sa(t_ps_stat *ps_stat)
{
	my_swap(ps_stat->stack_a);
}

void	sb(t_ps_stat *ps_stat)
{
	my_swap(ps_stat->stack_b);
}

void	ss(t_ps_stat *ps_stat)
{
	my_swap(ps_stat->stack_a);
	my_swap(ps_stat->stack_b);
}

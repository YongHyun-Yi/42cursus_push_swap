/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_instructions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:19:23 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/27 16:58:39 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	pa(t_ps_stat *ps_stat)
{
	my_push(&ps_stat->stack_a, &ps_stat->stack_b);
}

void	pb(t_ps_stat *ps_stat)
{
	my_push(&ps_stat->stack_b, &ps_stat->stack_a);
}
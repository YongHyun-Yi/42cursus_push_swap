/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_instructions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:19:23 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/20 18:00:23 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_ps_stat *ps_stat)
{
	my_swap(ps_stat->stack_a);
	ps_stat->com_cnt++;
}

void	pa(t_ps_stat *ps_stat)
{
	my_push(&ps_stat->stack_a, &ps_stat->stack_b);
	ps_stat->com_cnt++;
}

void	ra(t_ps_stat *ps_stat)
{
	my_rotate(&ps_stat->stack_a);
	ps_stat->com_cnt++;
}

void	rra(t_ps_stat *ps_stat)
{
	my_reverse_rotate(&ps_stat->stack_a);
	ps_stat->com_cnt++;
}

void	n_ra(t_ps_stat *ps_stat, long long cnt)
{
	while (cnt)
	{
		if (cnt > 0)
		{
			ra(ps_stat);
			cnt--;
		}
		else
		{
			rra(ps_stat);
			cnt++;
		}
	}
	return ;
}

void	sb(t_ps_stat *ps_stat)
{
	my_swap(ps_stat->stack_b);
	ps_stat->com_cnt++;
}

void	pb(t_ps_stat *ps_stat)
{
	my_push(&ps_stat->stack_b, &ps_stat->stack_a);
	ps_stat->com_cnt++;
}

void	rb(t_ps_stat *ps_stat)
{
	my_rotate(&ps_stat->stack_b);
	ps_stat->com_cnt++;
}

void	rrb(t_ps_stat *ps_stat)
{
	my_reverse_rotate(&ps_stat->stack_b);
	ps_stat->com_cnt++;
}

void	n_rb(t_ps_stat *ps_stat, long long cnt)
{
	while (cnt)
	{
		if (cnt > 0)
		{
			rb(ps_stat);
			cnt--;
		}
		else
		{
			rrb(ps_stat);
			cnt++;
		}
	}
	return ;
}

void	ss(t_ps_stat *ps_stat)
{
	sa(ps_stat);
	sb(ps_stat);
}

void	rr(t_ps_stat *ps_stat)
{
	ra(ps_stat);
	rb(ps_stat);
}

void	rrr(t_ps_stat *ps_stat)
{
	rra(ps_stat);
	rrb(ps_stat);
}

void	n_rr(t_ps_stat *ps_stat, long long cnt)
{
	while (cnt)
	{
		if (cnt > 0)
		{
			rr(ps_stat);
			cnt--;
		}
		else
		{
			rrr(ps_stat);
			cnt++;
		}
	}
	return ;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_instructions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:19:23 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/23 08:54:56 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_ps_stat *ps_stat)
{
	my_swap(ps_stat->stack_a);
	// ps_stat->com_cnt++;
	my_add_inst(&ps_stat->inst_lst, "sa\n");
}

void	pa(t_ps_stat *ps_stat)
{
	my_push(&ps_stat->stack_a, &ps_stat->stack_b);
	// ps_stat->com_cnt++;
	my_add_inst(&ps_stat->inst_lst, "pa\n");
}

void	ra(t_ps_stat *ps_stat)
{
	my_rotate(&ps_stat->stack_a);
	// ps_stat->com_cnt++;
	my_add_inst(&ps_stat->inst_lst, "ra\n");
}

void	rra(t_ps_stat *ps_stat)
{
	my_reverse_rotate(&ps_stat->stack_a);
	// ps_stat->com_cnt++;
	my_add_inst(&ps_stat->inst_lst, "rra\n");
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
	// ps_stat->com_cnt++;
	my_add_inst(&ps_stat->inst_lst, "sb\n");
}

void	pb(t_ps_stat *ps_stat)
{
	my_push(&ps_stat->stack_b, &ps_stat->stack_a);
	// ps_stat->com_cnt++;
	my_add_inst(&ps_stat->inst_lst, "pb\n");
}

void	rb(t_ps_stat *ps_stat)
{
	my_rotate(&ps_stat->stack_b);
	// ps_stat->com_cnt++;
	my_add_inst(&ps_stat->inst_lst, "rb\n");
}

void	rrb(t_ps_stat *ps_stat)
{
	my_reverse_rotate(&ps_stat->stack_b);
	// ps_stat->com_cnt++;
	my_add_inst(&ps_stat->inst_lst, "rrb\n");
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
	my_swap(ps_stat->stack_a);
	my_swap(ps_stat->stack_b);
	// ps_stat->com_cnt++;
	my_add_inst(&ps_stat->inst_lst, "ss\n");
}

void	rr(t_ps_stat *ps_stat)
{
	my_rotate(&ps_stat->stack_a);
	my_rotate(&ps_stat->stack_b);
	// ps_stat->com_cnt++;
	my_add_inst(&ps_stat->inst_lst, "rr\n");
}

void	rrr(t_ps_stat *ps_stat)
{
	my_reverse_rotate(&ps_stat->stack_a);
	my_reverse_rotate(&ps_stat->stack_b);
	// ps_stat->com_cnt++;
	my_add_inst(&ps_stat->inst_lst, "rrr\n");
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
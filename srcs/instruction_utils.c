/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:59:46 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/27 17:01:30 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

int	my_add_inst(t_list **inst_lst, char *str)
{
	t_list	*new_node;

	new_node = ft_lstnew(str);
	if (!new_node)
		return (FAIL);
	ft_lstadd_back(inst_lst, ft_lstnew(str));
	return (SUCCESS);
}

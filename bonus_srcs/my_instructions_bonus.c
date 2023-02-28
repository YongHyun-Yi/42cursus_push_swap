/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_instructions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:53:59 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/27 17:00:57 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	my_swap(t_dlist *my_stack)
{
	int temp;

	if (!my_stack || !my_stack->next)
		return ;
	temp = my_stack->value;
	my_stack->value = (my_stack->next)->value;
	(my_stack->next)->value = temp;
	return ;
}

t_dlist	*my_pop(t_dlist **my_stack)
{
	t_dlist	*target_node;

	target_node = *my_stack;
	if (!target_node)
		return (NULL);
	if (target_node->next != target_node)
	{
		(target_node->prev)->next = target_node->next;
		(target_node->next)->prev = target_node->prev;
		*my_stack = target_node->next;
	}
	else
		*my_stack = NULL;
	return (target_node);
}

void	my_push(t_dlist **dest, t_dlist **src)
{
	t_dlist	*target_node;

	target_node = my_pop(src);
	if (target_node)
		ft_cir_dlstadd_front(dest, target_node);
}

void	my_rotate(t_dlist **my_stack)
{
	if (!my_stack || !(*my_stack)->next)
		return ;
	(*my_stack) = (*my_stack)->next;
}

void	my_reverse_rotate(t_dlist **my_stack)
{
	if (!my_stack || !(*my_stack)->prev)
		return ;
	(*my_stack) = (*my_stack)->prev;
}

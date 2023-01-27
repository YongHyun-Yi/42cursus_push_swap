/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_instructions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:53:59 by yonghyle          #+#    #+#             */
/*   Updated: 2023/01/27 09:33:39 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap_a(t_ft_list **stack_a);
void	swap_b(void);
void	swap_a_swap_b(void);
void	push_a(t_ft_list **stack_a, t_ft_list **stack_b);
void	push_b(void);
void	rotate_a(t_ft_list **stack_a);
void	rotate_b(void);
void	rotate_a_rotate_b(void);
void	reverse_rotate_a(void);
void	reverse_rotate_b(void);
void	reverse_rotate_a_rotate_b(void);

void	swap_a(t_ft_list **stack_a)
{
	t_ft_list	*first_node;
	t_ft_list	*second_node;
	t_ft_list	*temp_node;

	if (*stack_a && (*stack_a)->next)
	{
		first_node = *stack_a;
		second_node = first_node->next;
		temp_node = second_node->next;
		second_node->next = first_node;
		first_node->next = temp_node;
		*stack_a = second_node;
	}
	return ;
}
	// 가장 상위 2개의 노드를 교환
	// 서로의 next만 교환하고 head의 주소만 변경

void	push_a(t_ft_list **stack_a, t_ft_list **stack_b)
{
	t_ft_list	*temp_node;

	temp_node = *stack_b;
	*stack_b = (*stack_b)->next;
	temp_node->next = *stack_a;
	*stack_a = temp_node;
}
	// temp를 b의 헤더로
	// b의 헤더를 b의 next로
	// temp의 next를 a의 헤더로
	// a의 헤더를 temp로

void	rotate_a(t_ft_list **stack_a)
{
	t_ft_list	*last_node;

	last_node = *stack_a;
	while (last_node->next)
		last_node = last_node->next;
	last_node->next = *stack_a;
	*stack_a = (*stack_a)->next;
	(last_node->next)->next = NULL;
}
	// last의 next를 헤더로
	// 헤더를 헤더의 next로
	// last의 next의 next를 null로
	

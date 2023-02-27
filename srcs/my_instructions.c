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

#include "push_swap.h"

void	my_swap(t_dlist *my_stack)
{
	int temp;

	if (!my_stack || !my_stack->next)
		return ;
	// 리스트가 비어있거나 노드가 하나만 있을때는 작업을 수행하지 않는다
	// 리스트가 null 포인터인 경우를 먼저 체크해서 세그폴트에 대비한다
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
	if (target_node->next != target_node) // 리스트에 노드가 둘 이상 있을경우
	{
		(target_node->prev)->next = target_node->next;
		(target_node->next)->prev = target_node->prev;
		*my_stack = target_node->next;
		// 나머지 노드들을 연결해주고 헤더를 변경한다
	}
	else // 노드가 하나만 있을경우
		*my_stack = NULL;
		// 헤더가 가리키는 노드는 없다
	return (target_node);
}

void	my_push(t_dlist **dest, t_dlist **src)
{
	t_dlist	*target_node;

	target_node = my_pop(src);
	// 안전하게 타겟 노드의 연결을 끊고 반환한다
	if (target_node)
		ft_cir_dlstadd_front(dest, target_node);
		// 원형 양방향 연결리스트의 함수로 push를 구현한다
}

void	my_rotate(t_dlist **my_stack)
{
	if (!my_stack || !(*my_stack)->next)
		return ;
	(*my_stack) = (*my_stack)->next;
	// 맨 위의 요소가 밑으로 넘어간다
}

void	my_reverse_rotate(t_dlist **my_stack)
{
	if (!my_stack || !(*my_stack)->prev)
		return ;
	(*my_stack) = (*my_stack)->prev;
	// 맨 아래의 요소가 위로 넘어간다
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_instructions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:53:59 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/16 15:45:18 by yonghyle         ###   ########.fr       */
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
void	reverse_rotate_a(t_ft_list **stack_a);
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

void	reverse_rotate_a(t_ft_list **stack_a)
{
	t_ft_list	*prev_node;
	t_ft_list	*cur_node;

	prev_node = NULL;
	cur_node = *stack_a;
	while (cur_node->next)
	{
		prev_node = cur_node;
		cur_node = cur_node->next;
	}
	cur_node->next = *stack_a;
	*stack_a = cur_node;
	prev_node->next = NULL;
}
	// last의 next를 헤더로
	// prev의 next를 null로
	// 헤더를 last로

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

void	my_push(t_dlist *dest, t_dlist *src)
{
	// 아직 모르겠다
	// 넘겨주는 쪽과 받는 쪽 둘다 이중포인터로 받나...?
	// 넘겨주는 쪽에서는 해당 노드의 prev와 next를 서로 연결해서
	// 넘겨줄 노드를 완전히 분리 시킨다
	// 넘겨주는 쪽 헤더를 한칸 당긴다

	// 넘겨줄 노드를 받는 쪽의 헤더로 추가한다
	// '받는쪽 헤더'의 prev와 '받는쪽 헤더의 prev'의 next를
	// 넘겨줄 노드로 설정한다...?
	// 넘겨줄 노드의 prev와 next도 수정해야한다...굉장히 번거로움

	// 단순 리스트에 노드를 추가하는것은 문제가 안되지만
	// 원형 큐와 비슷하게 구현하였기 때문에 수정해야 하는 포인터가
	// next외에도 prev가 있어 두배로 늘어난다...
	// lstadd_front와 비슷하게 구현하여 해당 함수를 호출하고
	// prev를 연결하는 작업만 수행할것인지?
	// 처음에 파싱하고 추가할때는 lstadd_back을 비슷하게 구현하여
	// 해당 함수에서 사용하려고 만들었지만 사용하지 못한 prev_node 변수를
	// 사용해서 prev를 설정하기...?

	// 두 스택 모두 헤더에 대해 작업이 수행되기 때문에
	// 헤더를 수정해야하므로 이중포인터로 값을 받아야 한다

	// 우선 넘겨주는 쪽은 리스트가 비어있는지 확인해야한다
	// 받는 쪽은 비어있든 아니든 상관없다

	// 도대체 어떻게 해야 유연하게 사용할수있을까....
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
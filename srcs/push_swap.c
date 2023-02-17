/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:48:27 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/17 11:37:11 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

void	ft_cir_dlstadd_back(t_dlist **lst, t_dlist *new)
{
	if (!*lst) // list가 비어있을때, '리스트의 헤더를 담당하는 노드'의 '주소값'을 넘겨줌, 노드가 가진 주소값이 아니라 노드 자체의 주소값임
	{
		*lst = new;
		new->prev = new;
		new->next = new;
	}
	else
	{
		new->prev = (*lst)->prev;
		new->next = *lst;
		(new->prev)->next = new;
		(new->next)->prev = new;
	}
}

void	ft_cir_dlstadd_front(t_dlist **lst, t_dlist *new)
{
	ft_cir_dlstadd_back(lst, new);
	if ((*lst)->next != *lst)
		*lst = (*lst)->prev;
		// 헤더만 옮겨준다
}

t_ps_stat *push_swap_parsing(char *argv[])
{
	t_ps_stat	*ps_stat; // 전역변수를 사용할수 없으니 stack 들을 가리킬 변수가 필요하다
	char 		*bit_masking; // 비트마스킹은 모든 인자에 대해서 수행해야 함으로 가장 상위에 존재한다
	char 		**split_argv; // 인자로 받은 문자열 안에서 공백을 기준삼아 다수의 문자열로 쪼개질 가능성을 염두하고 split을 수행한다
	int 		num;
	t_dlist 	*new_node;

	ps_stat = calloc(1, sizeof(t_ps_stat)); // 할당 후 0으로 초기화 해줘야하니 calloc 을 사용
	bit_masking = ft_calloc((UINT_MAX / 8) + 1, sizeof(char));
	if (!ps_stat || !bit_masking)
		return (NULL);
	
	while (*argv) // 인자 한 덩어리 기준으로 작업을 시작
	{
		split_argv = ft_split(*argv, ' '); // 인자가 기본단위인 문자열이 될때까지 쪼갠다
		while (*split_argv) // 기본단위인 문자열을 기준으로 본격적인 작업을 시작
		{
			if (!ft_strisint(*split_argv)) // 숫자이고 int 범위인가?
			{
				ft_printf("arguments are not int!\n");
				return (FAIL);
			}
			
			num = ft_atoi(*split_argv);
			
			if (!ft_check_intdup(bit_masking, num)) // 중복되는 수가 들어왔는가?
			{
				ft_printf("arguments are dup!\n");
				return (FAIL);
			}

			new_node = calloc(1, sizeof(t_dlist));
			new_node->value = num;
			ft_cir_dlstadd_back(&ps_stat->stack_a, new_node);

			split_argv++; // 다음 문자열을 살펴본다
		}
		argv++; // 모든 문자열을 살펴봤으면 다음 인자를 살펴본다
	}
	return (ps_stat); // 파싱을 끝내고 stack 들이 들어있는 구조체를 반환한다
	// 어차피 여기전 파싱하고 stack_a 에 넣어주는거만 하는데 stack_a 만 관리해서 반환하는게 맞지 않을까...?
}

void	print_my_stack(t_dlist *my_stack)
{
	t_dlist *cur_node;

	cur_node = my_stack;
	while (cur_node)
	{
		ft_printf("%d ", cur_node->value);
		if (cur_node->next == my_stack)
			break ;
		cur_node = cur_node->next;
	}
	ft_printf("\n");
	return ;
}

void	print_all_my_stack(t_ps_stat *ps_stat)
{
	ft_printf("\n");
	ft_printf("======== << print stack >> ========\n");
	ft_printf("\n");
	ft_printf("stack a: ");
	print_my_stack(ps_stat->stack_a);
	ft_printf("stack b: ");
	print_my_stack(ps_stat->stack_b);
	ft_printf("\n");
	ft_printf("===================================\n");
	ft_printf("\n");

	return ;
}

int main(int argc, char *argv[])
{
	t_ps_stat *ps_stat;
	// gnl에서 static 으로 다중 변수용 구조체를 들고 시작했던것처럼
	// 여기서도 main 에서 미리 만들고 시작하는게 좋지 않을까...?
	// 문자열도 null 대신 빈 문자열로 초기화 했던것처럼...
	// stack 두개는 calloc으로 빈 배열로써 시작하지만
	// exit 함수에서 null 포인터인지에 따라 해제할지 말지 결정한다

	if (argc < 2)
		exit(EXIT_SUCCESS);

	ps_stat = push_swap_parsing(argv + 1);
	if (ps_stat == FAIL)
		return (FAIL);
		// 반환값으로 성공 실패여부를 확인하기 위해
		// 반환받을 변수를 따로 파긴 했지만...
		// 구조체를 미리 초기화해서 구조체를 넘겨주고
		// 그 안에 있는 stack_a 가 null 인지를 체크하는것은...?
		// 그럼 void 로 수행?

	print_all_my_stack(ps_stat);
	// 구조체를 넘겨주는게 아니라 여기서 stack_a만 반환받는것은...?

	my_push(&ps_stat->stack_b, &ps_stat->stack_a);
	my_push(&ps_stat->stack_b, &ps_stat->stack_a);
	my_push(&ps_stat->stack_b, &ps_stat->stack_a);

	print_all_my_stack(ps_stat);

	my_push(&ps_stat->stack_a, &ps_stat->stack_b);

	print_all_my_stack(ps_stat);

	// ft_putstr_fd("Error\n", 2); // 에러는 stderr로 출력해야 한다
	// exit(EXIT_FAILURE);
}

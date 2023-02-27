/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:48:27 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/27 17:09:32 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_inst_lst(void *str)
{
	ft_printf("%s\n", str);
}

int ft_is_stack_sorted(t_dlist *my_stack)
{
	t_dlist	*cur_node;

	if (!my_stack)
		return (FAIL);
	cur_node = my_stack;
	while (cur_node->next != my_stack) // 다음 노드가 헤더라면, 마지막 노드까지 왔다 즉, 문제없이 한 바퀴 돌았다면 끝
	{
		if (!dlist_valcmp(cur_node, cur_node->next)) // 다음 노드보다 값이 크면 즉, 오름차순이 아니면
			return (FAIL);
		cur_node = cur_node->next;
	}
	return (SUCCESS);
}

// int	ft_is_allstack_sorted(t_ps_stat *ps_stat)
// {
// 	// stack_b 가 비어있고 stack_a 가 모두 정렬되어있어야함

// 	if (ps_stat->stack_b || !ps_stat->stack_a)
// 		return (FAIL);
// 	return (ft_is_stack_sorted(ps_stat->stack_a));
// }

// void	print_my_stack(t_dlist *my_stack)
// {
// 	t_dlist *cur_node;

// 	cur_node = my_stack;
// 	while (cur_node)
// 	{
// 		ft_printf("%d ", cur_node->value);
// 		if (cur_node->next == my_stack)
// 			break ;
// 		cur_node = cur_node->next;
// 	}
// 	ft_printf("\n");
// 	return ;
// }

// void	print_all_my_stack(t_ps_stat *ps_stat)
// {
// 	ft_printf("\n");
// 	ft_printf("======== << print stack >> ========\n");
// 	ft_printf("\n");
// 	ft_printf("stack a: ");
// 	print_my_stack(ps_stat->stack_a);
// 	ft_printf("stack b: ");
// 	print_my_stack(ps_stat->stack_b);
// 	ft_printf("\n");
// 	ft_printf("===================================\n");
// 	ft_printf("\n");

// 	return ;
// }

int	push_swap_parsing(t_ps_stat *ps_stat, char *argv[])
{
	char 		*bit_masking; // 비트마스킹은 모든 인자에 대해서 수행해야 함으로 가장 상위에 존재한다
	char 		**split_argv; // 인자로 받은 문자열 안에서 공백을 기준삼아 다수의 문자열로 쪼개질 가능성을 염두하고 split을 수행한다
	int 		num;
	t_dlist 	*new_node;

	bit_masking = ft_calloc((UINT_MAX / 8) + 1, sizeof(char));
	
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
			if (!new_node)
			{
				ft_printf("malloc fail!\n");
				return (FAIL);
			}
			new_node->value = num;
			ft_cir_dlstadd_back(&ps_stat->stack_a, new_node);

			split_argv++; // 다음 문자열을 살펴본다
		}
		// free(split_argv); // 올바른 free를 위해서는 인덱스로 쓸 변수를 만들어 원래 주소를 보존해야 한다
		argv++; // 모든 문자열을 살펴봤으면 다음 인자를 살펴본다
	}
	free(bit_masking);
	return (SUCCESS);
}

int main(int argc, char *argv[])
{
	t_ps_stat ps_stat;

	if (argc < 2)
		return (0);
	ft_bzero(&ps_stat, sizeof(t_ps_stat));
	if (!push_swap_parsing(&ps_stat, argv + 1))
		exit(EXIT_FAILURE); // my_exit 만들어서 호출할것

	print_all_my_stack(&ps_stat);

	if (ft_is_stack_sorted(ps_stat.stack_a) && ps_stat.stack_b == NULL)
		return (EXIT_SUCCESS);
	
	my_push_swap_solve(&ps_stat);

	// ft_printf("\n - finish! - \n\n");

	// print_all_my_stack(ps_stat);

	// ft_lstiter(ps_stat->inst_lst, print_inst_lst);

	// ft_printf("\ninstruction optimizing...\n\n");
	// inst_lst_optimizing(ps_stat->inst_lst); // 뭔가 문제있음

	ft_lstiter(ps_stat.inst_lst, print_inst_lst);

	ft_lstclear(&ps_stat.inst_lst, NULL);

	// ft_putstr_fd("Error\n", 2); // 에러는 stderr로 출력해야 한다
	// exit(EXIT_FAILURE);
}

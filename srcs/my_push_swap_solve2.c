/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_push_swap_solve2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 09:46:54 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/24 18:25:37 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// get biggest sorted
// bubble sort or quick sort
// divide 2 group
// divide 3 group <- 그냥 인자 갯수에 따라 청크 갯수를 나눠주는식으로 해도 될듯...?

void	inst_lst_optimizing(t_list *inst_lst)
{
	// 명령어가 담긴 리스트를 순회하며 합칠수있거나 지울수있는거 처리하기
	// 대신 push를 만나면 그 다음 push가 아닌 명령어 찾아서 기준점(?) 삼기
	// -> push는 두 리스트 모두에게 영향을 주니까 최적화를 할수없다 by. jmaing
	//
	// 단일 연결리스트이므로 libft 함수를 사용가능하다
	// lstiter를 사용해도 될듯...? 현재 노드부터 시작해서 자신 뒤에 있는 노드들만 보면됨
	// pa pb 나오는순간 return ; 으로 종료
	// 나머지는 현재 선택한 명령어의 종류에 따라 줄일수 있는 케이스에 한해서만 줄이기
	// list도 dlist처럼 pop을 따로 만들껄 그랬나, delnode에서 연결은 해주지만
	// list에서 노드를 뽑아내면서 연결하는것 따로, free하는거 따로 조합하는식으로 구현하는게
	// 좀 더 모듈화에 좋지 않았을까...
	// 현재 선택한 노드도 pa pb라면 바로 return ; 으로 종료하고 다음 iter로 넘어간다
	//
	// ra - rra(둘 다 삭제), rb(rr), rrr(rrb)
	// rra - ra(둘 다 삭제), rrb(rrr), rr(rb)
	// rb - rrb(둘 다 삭제), ra(rr), rrr(rra)
	// rrb - rb(둘 다 삭제), rra(rrr), rr(ra)
	// rr - rra(rb), rrb(ra)
	// rrr - ra(rrb), rb(rra)
	// sa - sb(ss)
	// sb - sa(ss)
	printf("%s\n", (char *)(inst_lst->content));
}

// t_dlist *get_lis_node(t_dlist *target_node, t_dlist *idx_lst)
// {
// 	// 이 함수는 my_stack과 idx_lst를 역으로 순회하며 검사하는 함수
// 	if ((idx_lst->prev)->value == get_largest_node(idx_lst)->value)
// 	return (0);
// }

size_t get_lis_idx(t_dlist *target_node, t_dlist *idx_lst)
{
	size_t	cur_idx;
	t_dlist	*val_cmp_node;
	t_dlist	*idx_cmp_node;

	if (idx_lst == NULL)
		return (1);
	cur_idx = get_largest_node(idx_lst)->value;
	val_cmp_node = target_node->prev;
	idx_cmp_node = idx_lst->prev;
	while (1)
	{
		if ((int)cur_idx == idx_cmp_node->value)
		{
			if (target_node->value > val_cmp_node->value)
				return (cur_idx + 1);
			if (cur_idx == 1)
				return (1);
			cur_idx--;
		}
		val_cmp_node = val_cmp_node->prev;
		idx_cmp_node = idx_cmp_node->prev;
	}
}

t_dlist *get_lis_idx_list(t_dlist *my_stack)
{
	t_dlist *idx_lst;
	t_dlist *cur_node;
	t_dlist *new;

	idx_lst = NULL;
	cur_node = my_stack;
	while (1)
	{
		new = ft_dlstnew(get_lis_idx(cur_node, idx_lst));
		if (!new)
			return (FAIL);
		ft_cir_dlstadd_back(&idx_lst, new);
		if (cur_node->next == my_stack)
			break ;
		cur_node = cur_node->next;
	}
	return (idx_lst);
}

t_dlist *get_lis_list(t_dlist *my_stack)
{
	t_dlist *idx_list;
	t_dlist *lis_list;

	idx_list = get_lis_idx_list(my_stack);
	lis_list = NULL;

	// t_dlist *cur_node;
	// t_dlist *cur_idx_node;
	// t_dlist *new;
	// size_t	cur_idx = get_largest_node(idx_list)->value;
	// cur_node = my_stack->prev;
	// cur_idx_node = idx_list->prev;
	// while (1)
	// {
		// if (cur_idx_node->value == (int)cur_idx) // 항상 idx_list의 마지막 노드와 비교한다
		// {
		// 	new = ft_dlstnew(cur_node->value);
		// 	if (!new)
		// 		return (FAIL);
		// 	ft_cir_dlstadd_back(&lis_list, new);
		// 	cur_idx--;
		// }
		// if (cur_node->prev == my_stack->prev)
		// 	break ;
		// cur_node = cur_node->prev;
		// cur_idx_node = cur_idx_node->prev;

		// free(my_pop(&(idx_list->prev))); // 비교한 idx 노드는 삭제한다, cur node와 같은 위치를 가리키게 하도록 && 최댓값을 갱신하기 위해
		// if (cur_idx_node != idx_list)
		// {
		// 	(cur_idx_node->prev)->next = idx_list;
		// 	idx_list->prev = cur_idx_node->prev;
		// }
		// free(cur_idx_node);
	// }

	// my_stack, idx_list 를 인자로 받는 함수 작성
	// 얘네들의 주소값을 넘겨줘서 포인터 연산을 해서 작업을 수행
	// 한바퀴 다 돌았다는것을 어떻게 확인할것인지...?
	// 여태까지는 my_stack은 그대로 두고 값을 복사한 cur_node와 비교하여 확인하였음

	size_t	cur_idx;
	t_dlist *cur_node;
	t_dlist *new;
	cur_idx = get_largest_node(idx_list)->value;
	cur_node = my_stack->prev;
	idx_list = idx_list->prev;
	while (1)
	{
		if (idx_list->value == (int)cur_idx)
		{
			new = ft_dlstnew(cur_node->value);
			if (!new)
				return (FAIL);
			ft_cir_dlstadd_back(&lis_list, new);
			cur_idx--;
		}
		if (cur_node->prev == my_stack->prev)
			break ;
		cur_node = cur_node->prev;
		idx_list = idx_list->prev;
	}

	ft_printf("RETURNED LIS: ");
	size_t print_lis = 0;
	t_dlist *print_lis_lst = lis_list;
	while (print_lis < ft_cir_dlstsize(lis_list))
	{
		ft_printf("%d ", print_lis_lst->value);
		print_lis_lst = print_lis_lst->next;
		print_lis++;
	}
	ft_printf("\n");
	printf("LIS SIZE: %zu\n", ft_cir_dlstsize(lis_list));

	// t_dlist *temp = lis_list->prev;
	// free(my_pop(&(lis_list->prev)));

	// ft_printf("RETURNED LIS: ");
	// print_lis = 0;
	// print_lis_lst = lis_list;
	// while (print_lis < ft_cir_dlstsize(lis_list))
	// {
	// 	ft_printf("%d ", print_lis_lst->value);
	// 	print_lis_lst = print_lis_lst->next;
	// 	print_lis++;
	// }
	// ft_printf("\n");
	// printf("LIS SIZE: %zu\n", ft_cir_dlstsize(lis_list));

	// ft_printf("RETURNED LIS: ");
	// print_lis = 0;
	// print_lis_lst = lis_list->prev;
	// while (print_lis < ft_cir_dlstsize(lis_list))
	// {
	// 	ft_printf("%d ", print_lis_lst->value);
	// 	print_lis_lst = print_lis_lst->prev;
	// 	print_lis++;
	// }
	// ft_printf("\n");
	// printf("LIS SIZE: %zu\n", ft_cir_dlstsize(lis_list));

	return (0);
}

void	sort_under100_elements(t_ps_stat *ps_stat)
{
	get_lis_list(ps_stat->stack_a);
	// ft_is_stack_sorted(ps_stat->stack_a);
}
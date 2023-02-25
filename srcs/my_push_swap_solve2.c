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

void	get_lis_lst(t_dlist *my_stack)
{
	// 가장 긴 증가 수열
	// 비교는 항상 최대 인덱스를 가진 노드부터
	// 그 노드보다 크다면 최대 인덱스 + 1을 취득
	// 그렇지 않으면 더 작은 인덱스를 가진 노드와 비교하고
	// 가장 마지막에 가선 그 노드를 시작 인덱스로 삼게 되는 경우도 있음
	// 시작지점은 어디서 시작되던 상관없으나
	// 거꾸로 탐색했을때 최대 인덱스부터 해당 인덱스에 속하는 애들만 골라내면
	// 해당 수열 중에 존재하는 가장 긴 증가수열을 얻을 수 있음
	
	// 배열이 아니라 리스트인데 인덱스를 어떻게 매겨줄지 고민중...
	// 리스트와 같은 사이즈의 리스트를 만들고
	// 해당 리스트의 순서와 매칭시키고 value에는 인덱스를 매기기...? -> 나중에 void * content로 변경하면 더 유연해질듯
	// 최대 인덱스를 가진 노드부터 비교하려면 그냥 인덱스 매긴 리스트를 거꾸로 탐색하면 됨
	// 탐색하면서 최대 인덱스가 맞는지 우선 비교하고 맞다면 해당 인덱스와 같은 순서의 리스트와 값을 비교
	// 리스트에 노드를 모두 채워놓고 그다음 인덱스 매기는 작업을 해야하나...?
	// ex) 1 10 2 3 4 
	//     1  2 2 3 4
	// ex) 1 10 2 3 4 
	//     1  2 2 3 4
	// ex) 4 5 6 1 2
	//     1 2 3 1 2
	// ex) 4 5 6 1 2
	//     1 2 3 1 2
	// ex) 2 6 3 4 5 1 7
	//     1 2 2 3 4 1 5
	// ex) 2 6 3 4 5 1 7
	//     1 2 2 3 4 1 2
	// ex) 2 6 3 4 10 5 1 7 8 0
	//     1 2 2 3  4 4 1 5 6 1

	// 그냥 int 배열 두개만들어서 해버릴까...

	// 인덱스용 list만 새로 할당하고
	// 값을 넣어놓는건 원래 list를 추가하기만 하면
	// 나중에 비교함수를 사용해서도 활용하기 좋지 않을까...
	// pivot도 비슷하게?
	// -> lstadd_back을 하면 prev, next가 변경되기 때문에
	// 기존의 리스트가 변경될 여지가 있음, 기각...

	size_t	iter_max = 0;
	t_dlist *cur_node;
	t_dlist *cmp_node;

	t_dlist *idx_lst = NULL;
	t_dlist *idx_cur_node;
	t_dlist *idx_cmp_node;
	size_t	max_idx = 1;
	size_t	cur_idx = 1;
	
	ft_cir_dlstadd_back(&idx_lst, ft_dlstnew(cur_idx)); // 이전노드를 탐색할때 인덱스 리스트에서 세그폴트가 발생하지 않게 맨 처음 노드를 미리 추가하고 시작한다

	while (iter_max < ft_cir_dlstsize(my_stack))
	{
		
		cur_node = my_stack;
		idx_cur_node = idx_lst;
		
		size_t	iter_idx = 0;
		while (iter_idx < iter_max)
		{
			cur_node = cur_node->next;
			idx_cur_node = idx_cur_node->next;
			iter_idx++;
		}
		// 작업 시작점까지 이동
		// idx_list는 특정 사이즈만큼 한꺼번에 만들지 않는데
		// 그냥 header에서 prev로 가리키면 되지 않을까
		// 여기서 cur_node로 선택할 노드를 찾는부분을 함수로 따로 뺄까...?

		cmp_node = cur_node->prev;
		idx_cmp_node = idx_cur_node->prev;
		// 이전 노드부터 비교하며 시작
		//
		// 이 부분도 함수로 뺄까...현재 노드랑 인덱스 리스트를 넘겨주면
		// 알아서 비교해서 lis index를 반환하도록...?
		// 현재 노드랑 현재 노드의 스택을 안보내줘도 되는 이유는
		// header까지 탐색을 끝마쳐야 하는게 아니라 idx가 1이 될때까지
		// 혹은 대소비교에서 크다면 바로 끝마치기때문
		// 한바퀴 돌아버린것과는 문제가 없다
		// max idx는 get largest node로 idx lst에서 구한다
		// 현재 노드와 idx lst 를 매개변수로 쓴다
		//
		// get_lis_lst, get_lis_idx_lst, get_lis_idx
		// get_lis_lst에서 lis_idx_lst로 lis노드를 골라내고
		// lis lst에 addback으로 추가
		// lis node 구하는 과정에서 필요없는 lis idx는 pop, free 한다
		// 항상 비교작업에서 유효한 마지막 노드부터 시작하기 위함

		cur_idx = max_idx;
		while (iter_idx)
		{
			// 인덱스 리스트 값 비교, 원래 리스트 값 비교, 부합하지 않으면 두 리스트 모두 한칸씩 이전으로 당기기, cur idx값 줄이기
			// 인덱스 리스트 값이 cur idx와 같다면 비교를 시작한다, 그렇지 않으면 (두 리스트 모두 한칸씩 이전으로 당긴다)
			// 현재 노드와 비교할 노드의 값을 비교한다, 현재 노드가 더 크다면 인덱스 리스트에 cur idx + 1 값으로 새로운 노드를 추가한다
			// 그렇지 않다면 cur idx - 1 값을 가진채 (두 리스트 모두 한칸씩 이전으로 당긴다)
			if (idx_cmp_node->value == (int)cur_idx)
			{
				if (cur_node->value > cmp_node->value)
				{
					cur_idx++;
					if (cur_idx > max_idx)
						max_idx = cur_idx;
					ft_cir_dlstadd_back(&idx_lst, ft_dlstnew(cur_idx));
					break ;
				}
				if (cur_idx == 1) // 1 까지 내려왔으면 그냥 추가
					ft_cir_dlstadd_back(&idx_lst, ft_dlstnew(1));
				cur_idx--;
			}
			cmp_node = cmp_node->prev;
			idx_cmp_node = idx_cmp_node->prev;
			iter_idx--;
		}
		iter_max++;
	}

	t_dlist *print_ori_lst;
	t_dlist *print_idx_lst;
	print_ori_lst = my_stack;
	print_idx_lst = idx_lst;
	size_t print_idx;
	size_t print_max;
	print_idx = 0;
	print_max = ft_cir_dlstsize(my_stack);
	ft_printf("ORI: ");
	while (print_idx < print_max)
	{
		ft_printf("%d ", print_ori_lst->value);
		print_ori_lst = print_ori_lst->next;
		print_idx++;
	}
	ft_printf("\n");
	ft_printf("LIS: ");
	print_idx = 0;
	while (print_idx < print_max)
	{
		ft_printf("%d ", print_idx_lst->value);
		print_idx_lst = print_idx_lst->next;
		print_idx++;
	}
	ft_printf("\n");

	t_dlist *lis_lst = NULL;

	cur_node = my_stack->prev;
	idx_cur_node = idx_lst->prev;
	cur_idx = max_idx;
	while (cur_idx)
	{
		if (idx_cur_node->value == (int)cur_idx)
		{
			t_dlist *new = ft_dlstnew(cur_node->value);
			if (!new)
				return ;
			ft_cir_dlstadd_back(&lis_lst, new);
			cur_idx--;
		}
		cur_node = cur_node->prev;
		idx_cur_node = idx_cur_node->prev;
	}

	ft_printf("RETURNED LIS: ");
	size_t print_lis = 0;
	t_dlist *print_lis_lst = lis_lst;
	while (print_lis < max_idx)
	{
		ft_printf("%d ", print_lis_lst->value);
		print_lis_lst = print_lis_lst->next;
		print_lis++;
	}
	ft_printf("\n");
	printf("LIS LIST SIZE: %zu\n", ft_cir_dlstsize(lis_lst));
	
	// 인덱스 리스트와 오리지널 리스트를 순회하며
	// 인덱스 리스트의 값 비교에 따라 오리지널 리스트의 값을 가진
	// 새 d_list 리스트를 만들기?

	// 아니면 시작부터 오리지널 리스트의 값들을 가진 사본을 만들고
	// 인덱스 리스트 마킹후 인덱스 리스트의 값 비교에 따라
	// 특정 노드들 pop, free 하기?

	// my_stack 을 전부 순회
	// cur_node - my_stack 순회하는 노드
	// cmp_node - 비교할 노드
	
	// cmp_node = cur_node->prev
	// if cur_idx > 1
	//  if cur_idx == prev_idx
	//   if cur_node > cmp_node
	//    lstadd(idx_lst->value + 1)
	//   prev_idx--
	//   cmp_node--
	// else
	//  lstadd(1)

	// 맨 처음 노드를 인덱스 리스트에 1을 추가한채 시작한다, 매 반복문마다 시작점은 한칸씩 전진한다
	// 비교 전에 원래 리스트와 인덱스 리스트를 같은 위치까지 가리킨다 (새로 추가할 위치 && 새로 검사할 위치)
	// cur idx와 비교할 인덱스 리스트의 value와 같다면, 원래 리스트의 현재 노드와 새로 검사할 노드의 값을 비교한다
	// 만약 새로 검사할 노드의 값이 더 크다면 인덱스 리스트 맨 뒤에 현재 인덱스 리스트 value = cur_idx + 1 을 갖는 노드를 추가한다
	// max_idx 가 인덱스 리스트의 맨 마지막 노드의 값보다 작으면 갱신한다
	// 그렇지 않다면 cur idx를 1 감소시킨다
	// 원래 리스트와 인덱스 리스트 모두 이전 노드를 가리키며 계속한다
	// cur idx 가 1로 줄어들면 인덱스 리스트 맨 뒤에 value = 1 을 갖는 노드를 추가하고 다음단게로 넘어간다

	// int *ori_arr;
	// size_t	ori_arr_size = ft_cir_dlstsize(my_stack);
	// ori_arr = (int *)malloc(sizeof(int) * ori_arr_size);
	// if (!ori_arr)
	// 	return (FAIL);
	// t_dlist *cur_node;
	// cur_node = my_stack;
	// size_t	idx = 0;
	// while (idx < ori_arr_size)
	// {
	// 	ori_arr[idx] = cur_node->value;
	// 	cur_node = cur_node->next;
	// 	idx++;
	// }

	// idx = 0;
	// while (idx < ori_arr_size)
	// {
	// 	ft_printf("ori arr[%d]: %d\n", (int)idx, ori_arr[idx]);
	// 	idx++;
	// }

	// int *lis_arr;
	// return (0);
}

// stack_b에 두개 이상의 노드가 있을때
// get_total_rotcnt 를 기준으로 smallest node 를 탐색
// 동시 회전을 먼저 수행후 단일 회전 후 push
// 하나만 있을때는 탐색하지 않고 나머지 단계만 반복

void	sort_under100_elements(t_ps_stat *ps_stat)
{
	get_lis_lst(ps_stat->stack_a);
	// ft_is_stack_sorted(ps_stat->stack_a);
}
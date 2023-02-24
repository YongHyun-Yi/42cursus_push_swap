/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_push_swap_solve2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 09:46:54 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/24 14:26:50 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// get biggest sorted
// bubble sort or quick sort
// divide 2 group
// divide 3 group

int *get_lis_lst(t_dlist *my_stack)
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

	t_dlist *idx_lst;

	idx_lst = NULL;
	t_dlist *cur_node = my_stack;
	size_t	max_idx = 1;
	size_t	cur_idx;
	while (1)
	{
		t_dlist *serch_node = my_stack->prev; // 맨 마지막노드 부터
		cur_idx = max_idx;
		while (1)
		{
			if (cur_idx == 1)
				ft_cir_dlstadd_back(&idx_lst, ft_dlstnew(cur_idx));
			if (serch_node->value == cur_idx)
			serch_node = serch_node->prev;
		}
		if (cur_node->next == my_stack)
			break ;
	}

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
	// 만약 새로 검사할 노드의 값이 더 크다면 인덱스 리스트 맨 뒤에 현재 인덱스 리스트 value += 1 을 갖는 노드를 추가한다
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
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_push_swap_solve2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 09:46:54 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/23 12:01:41 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// get biggest sorted
// bubble sort or quick sort
// divide 2 group
// divide 3 group

void	get_biggest_sorted(t_dlist *my_stack)
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
	t_dlist *biggest_sorted_dlst;

	biggest_sorted_dlst = 0;
	t_dlist *cur_node = my_stack;
	size_t	max_idx = 0;
	size_t	cur_idx;
	while (1)
	{
		t_dlist *serch_node = my_stack;
		cur_idx = max_idx;
		while (1)
		{
			serch_node = serch_node->prev;
			if (serch_node->value == cur_idx)
		}
	}
}

// stack_b에 두개 이상의 노드가 있을때
// get_total_rotcnt 를 기준으로 smallest node 를 탐색
// 동시 회전을 먼저 수행후 단일 회전 후 push
// 하나만 있을때는 탐색하지 않고 나머지 단계만 반복

void	sort_under100_elements(t_ps_stat *ps_stat)
{
	ft_is_allstack_sorted(ps_stat);
}
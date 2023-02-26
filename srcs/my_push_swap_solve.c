/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_push_swap_solve.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:34:21 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/23 12:05:53 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int dlist_rotcmp2(t_dlist *src, t_dlist *a, t_dlist *b)
{
	if (my_abs(get_rotcnt_totop(src, a)) <= my_abs(get_rotcnt_totop(src, b)))
		return (1);
	// if (my_abs(get_rotcnt_totop(src, a)) == my_abs(get_rotcnt_totop(src, b)))
	// {
	// 	if (a->value < b->value)
	// 		return (1);
	// }
	return (0);
}

int dlist_rotcmp(t_dlist *dest, t_dlist *src, t_dlist *a, t_dlist *b)
{
	if (get_total_rotcnt(dest, src, a) <= get_total_rotcnt(dest, src, b))
		return (1);
	// if (get_total_rotcnt(dest, src, a) == get_total_rotcnt(dest, src, b))
	// {
	// 	if (a->value < b->value)
	// 		return (1);
	// 	// 일단은 동시회전이 이득이 아닐까...
	// 	// 두 리스트 간의 value를 비교하여 더 큰것을 먼저 넣어주는게 이득인 경우도 많다
	// }
	//
	// 조건을 간단하게 잡는게 가장 나았다...어째서...?
	// 총 회전수가 같을때 두 노드간의 값이라던지 동시회전수 비교같은건 의미가 없었나...?
	return (0);
}
// 비교함수 여러개를 준비하여 최소 최댓값 함수에 함수포인터 매개변수로 넘겨주려 했으나
// 비교함수 안에서 수행하는 함수마다 매개변수가 모두 다르기 때문에 일단 포기...
// void *로 비교할 매개변수들을 배열로 만들면 가능은 하겠지만...
// 모든 케이스를 완벽하게 커버할수는 없는것같다 ㅠㅠ

t_dlist *get_leastrot_node(t_dlist *dest, t_dlist *src)
{
	t_dlist *cur_node;
	t_dlist *least_node;

	cur_node = src;
	least_node = NULL;
	while (1)
	{
		if (least_node == NULL)
			least_node = cur_node;
		else if (dlist_rotcmp(dest, src, cur_node, least_node))
			least_node = cur_node;
		if (cur_node->next == src)
			break ;
		cur_node = cur_node->next;
	}
	return (least_node);
}
// 현재 src라는 리스트에 존재하는 노드 중 dest라는 리스트로 보내는
// 회전수가 가장 작은 노드를 반환한다
// 어떻게보면 이 함수 자체가 그리디 알고리즘이라고 할수있다...?

int	dlist_valcmp(t_dlist *a, t_dlist *b)
{
	return (a->value < b->value);
}

t_dlist *get_largest_node(t_dlist *my_stack)
{
	t_dlist *cur_node;
	t_dlist *max_node;

	cur_node = my_stack;
	max_node = cur_node;
	while (cur_node->next != my_stack)
	{
		cur_node = cur_node->next;
		if (!dlist_valcmp(cur_node, max_node))
			max_node = cur_node;
	}
	return (max_node);
}

t_dlist *get_smallest_node(t_dlist *my_stack)
{
	t_dlist *cur_node;
	t_dlist *min_node;

	cur_node = my_stack;
	min_node = cur_node;
	while (cur_node->next != my_stack)
	{
		cur_node = cur_node->next;
		if (dlist_valcmp(cur_node, min_node))
			min_node = cur_node;
	}
	return (min_node);
}

// 비교하는 함수를 함수포인터로 비워두었다
// 나중에 dlist의 content에 무엇이 들어있고 그것을 어떻게 가공을해서 비교를 하던
// 그에 따라 비교하는 알고리즘을 가진 함수를 함수 포인터 부분에 넘겨주면
// 알아서 최댓값과 최솟값을 가진 노드를 반환해준다
//
// 비교함수가 모두 (t_dlist *, t_dlist *)라는 매개변수를 가지는건 아니다...
// 회전수를 비교하는 비교함수를 만드는 상황만 보더라도
// 회전수를 구할때 dest와 src라는 매개변수를 추가로 요구하며
// 노드역할을 하는 t_dlist *는 하나뿐이다..
// 다시 원상태로 되돌린다

size_t	my_abs(long long nb)
{
	if (nb < 0)
		nb *= -1;
	return (nb);
}

long long	get_rotcnt_totop(t_dlist *my_stack, t_dlist *target_node)
{
	long long rot_cnt;
	t_dlist *cur_node;

	rot_cnt = 0;
	cur_node = my_stack;
	while (1)
	{
		if (cur_node == target_node)
			break ;
		rot_cnt++;
		cur_node = cur_node->next;
	}
	// if ((unsigned long long)rot_cnt > ft_cir_dlstsize(my_stack))
	// 	rot_cnt = -1;
	// else if ((unsigned long long)rot_cnt > ft_cir_dlstsize(my_stack) / 2)
	// 	rot_cnt -= ft_cir_dlstsize(my_stack);
	if ((unsigned long long)rot_cnt > ft_cir_dlstsize(my_stack) - rot_cnt)
		rot_cnt -= ft_cir_dlstsize(my_stack);
	// 정방향 회전과 역방향 회전 중 어느게 더 빠른지 계산한다
	return (rot_cnt);
}

long long	get_rotcnt_topos(t_dlist *my_stack, t_dlist *target_node)
{
	long long rot_cnt;
	t_dlist *cur_node;

	if (my_stack == NULL)
		return (0);
	if (target_node->value < get_smallest_node(my_stack)->value) // 최솟값
		return (get_rotcnt_totop(my_stack, get_smallest_node(my_stack)));
	else if (target_node->value > get_largest_node(my_stack)->value) // 최댓값
		return (get_rotcnt_totop(my_stack, get_smallest_node(my_stack)));
	rot_cnt = 0;
	cur_node = my_stack;
	while (!(target_node->value < cur_node->value && target_node->value > (cur_node->prev)->value)) // 사잇값
	{
		if (cur_node->next == my_stack)
			break ;
		rot_cnt++;
		cur_node = cur_node->next;
	}
	// if ((unsigned long)rot_cnt > ft_cir_dlstsize(my_stack))
	// 	rot_cnt = -1;
	// else if ((unsigned long)rot_cnt > ft_cir_dlstsize(my_stack) / 2)
	// 	rot_cnt -= ft_cir_dlstsize(my_stack);
	if ((unsigned long long)rot_cnt > ft_cir_dlstsize(my_stack) - rot_cnt)
		rot_cnt -= ft_cir_dlstsize(my_stack);
	// 정방향 회전과 역방향 회전 중 어느게 더 빠른지 계산한다
	return (rot_cnt);
}

long long	get_double_rotcnt(t_dlist *dest, t_dlist *src, t_dlist *target_node)
{
	long long dest_rotcnt;
	long long src_rotcnt;

	dest_rotcnt = get_rotcnt_topos(dest, target_node);
	src_rotcnt = get_rotcnt_totop(src, target_node);

	if ((dest_rotcnt == 0) || (src_rotcnt == 0))
		return (0);
	
	if ((dest_rotcnt > 0) != (src_rotcnt > 0))
	{
		// if (ft_cir_dlstsize(dest) - dest_rotcnt <= my_abs(dest_rotcnt) + my_abs(src_rotcnt))
		// 	dest_rotcnt -= ft_cir_dlstsize(dest);
		// else if (ft_cir_dlstsize(src) - src_rotcnt <= my_abs(dest_rotcnt) + my_abs(src_rotcnt))
		// 	src_rotcnt -= ft_cir_dlstsize(src);
		// 반대 회전을 구해서 동시회전으로 돌리는 횟수가
		// 최선의 회전수를 합친것보다 이득이면 반대 회전수를 취한다
		return (0);
	}

	// if (dest_rotcnt == src_rotcnt)
	// 	return (dest_rotcnt);
	// 	// 둘이 회전수가 같다면 둘중 하나로 반환한다
	
	if ((dest_rotcnt > 0) == (src_rotcnt > 0))
	{
		// printf("dest rotcnt: %lld\n", dest_rotcnt);
		// printf("src rotcnt: %lld\n", src_rotcnt);
		// if (my_abs(dest_rotcnt) < my_abs(src_rotcnt))
		// 	dest_rotcnt *= -1;
		// else
		// 	src_rotcnt *= -1;
		// printf("double rotcnt: %lld\n\n", dest_rotcnt + src_rotcnt);
		// return (dest_rotcnt + src_rotcnt);

		// 더 작은쪽의 부호를 반전시키고
		// 둘을 합하여 둘의 차이를 구한다
		// 최대 이만큼 동시 회전가능하다
		// 큰 쪽의 부호를 살리는 이유는 부호가 곧 방향이기 떄문
		//
		// 만약 ra 5 rb 1 이라면
		// 동시회전수는 5 - 1 인 4가 되나?
		// 땡 둘다 포함할수있는 1이 된다
		// 즉 작은쪽의 값을 그대로 반환하면 된다
		//
		// ra 6 rb 4 일때 -> 왜인진 모르겠지만 동시회전수가 2라고 생각함
		// 하지만 실제로 동시회전수는 4임, 그냥 산수 헛갈렷음 또...
		// 다만 음수 양수일때 대소구분은 주의할것
		// 아니지...여기서 부호는 방향일뿐 숫자만 놓고 비교해야한다

		if (my_abs(dest_rotcnt) > my_abs(src_rotcnt))
			return (src_rotcnt);
		return (dest_rotcnt);
	}
	return (0);
	// 불가한 경우에는 0을 반환

	// 헛갈린다
	// 둘다 최선의 회전수를 합쳤을때 이득일때가있고
	// 둘중 하나를 회전을 반전시켜서 둘중에 큰것을 취하는게 이득일때가 있다...
}

size_t	get_total_rotcnt(t_dlist *dest, t_dlist *src, t_dlist *target_node)
{
	long long dest_rotcnt;
	long long src_rotcnt;
	long long double_rotcnt;

	dest_rotcnt = get_rotcnt_topos(dest, target_node);
	src_rotcnt = get_rotcnt_totop(src, target_node);
	double_rotcnt = get_double_rotcnt(dest, src, target_node); //<< 이 놈이 범이이였음 ㅋㅋ;

	// printf("dest rotcnt: %lld\n", dest_rotcnt);
	// printf("src rotcnt: %lld\n", src_rotcnt);
	// printf("double rotcnt: %lld\n\n", double_rotcnt);

	if (double_rotcnt)
	{
		if (my_abs(dest_rotcnt) > my_abs(src_rotcnt))
		{
			// printf("return: %zu\n\n", my_abs(dest_rotcnt));
			return (my_abs(dest_rotcnt));
		}
		// printf("return: %zu\n\n", my_abs(src_rotcnt));
		return (my_abs(src_rotcnt));
	}
	// 동시회전이 가능하다면
	// 가장 큰 회전수를 그대로 반환해주면 된다
	// 결과적으로 동시회전 후 남은회전과 더하면 가장 큰 회전수와 같아지므로...
	//
	// 왜 동시회전수를 사용하지 않아야 더 적게 나오는거지...?
	// 같은 결과일텐데 이해가 안간다
	// printf("return: %zu\n\n", my_abs(dest_rotcnt) + my_abs(src_rotcnt));
	return (my_abs(dest_rotcnt) + my_abs(src_rotcnt));
	// 부호가 다르면 둘의 절댓값을 합친 횟수를 반환한다
}

void	sort_under5_elements(t_ps_stat *ps_stat)
{
	while (ft_cir_dlstsize(ps_stat->stack_a) > 3)
	{
		pb(ps_stat);
		// ft_printf("\ninitial push\n\n");
		// print_all_my_stack(ps_stat);
	} // biggest sort 로 대체 가능성 있음
	
	if (!ft_is_stack_sorted(ps_stat->stack_a))
	{
		sort_3_elements(ps_stat);
		// ft_printf("\n3 sort\n\n");
		// print_all_my_stack(ps_stat);
	}

	while (ps_stat->stack_b) // stack_b의 헤더가 null 이 될때까지
	{
		t_dlist *cur_node;

		cur_node = get_leastrot_node(ps_stat->stack_a, ps_stat->stack_b);
		n_rr(ps_stat, get_double_rotcnt(ps_stat->stack_a, ps_stat->stack_b, cur_node));
		n_ra(ps_stat, get_rotcnt_topos(ps_stat->stack_a, cur_node));
		n_rb(ps_stat, get_rotcnt_totop(ps_stat->stack_b, cur_node));
		pa(ps_stat);
		
		// ft_printf("\nsorting...\n\n");
		// print_all_my_stack(ps_stat);
	}
	// chunk만 나눠주면 완성될듯하다

	n_ra(ps_stat, get_rotcnt_totop(ps_stat->stack_a, get_smallest_node(ps_stat->stack_a)));

	return ;
}

void	sort_3_elements(t_ps_stat *ps_stat)
{
	t_dlist *my_stack;
	int		first;
	int		second;
	int		third;

	my_stack = ps_stat->stack_a;
	first = my_stack->value;
	second = (my_stack->next)->value;
	third = ((my_stack->next)->next)->value;

	if (first < second && !(second < third)) // 2 3 1
	{
		rra(ps_stat);
		if (!(third < first)) // 1 3 2 (sa, ra) (rra, sa)
			sa(ps_stat);
	}

	else if (second < third && third < first) // 3 1 2 (ra)
		ra(ps_stat);

	else // 2 1 3 (sa)
	{
		sa(ps_stat);
		if (!(second < third) && third < first) // 3 2 1 (ra, sa) (sa, rra)
			rra(ps_stat);
	}

	return ;
}

int	my_push_swap_solve(t_ps_stat *ps_stat)
{
	/*

		stack_a의 원소 갯수를 체크
		원소 갯수에 따라 하드코딩한 알고리즘으로 넘어가거나
		많은 원소를 정렬하는 알고리즘으로 넘어감

		많은 원소를 정렬하는 알고리즘에서는
		기존의 알고리즘들을 통해 원소들을 정렬하고
		거기서 적절한 pivot을 뽑아냄
		해당 pivot을 기준으로 가장 큰건 stack_a에
		두번째로 큰건 stack_b의 상단에
		가장 작은건 stack_b의 하단에 위치시킴

		순서대로 정렬하며 stack_a의 위에 쌓아올림

		하나의 stack 안에서 정렬할때 ra, rra, sa를 사용하면 되겠지만
		어디까지가 정렬되어 있는 원소인줄 알고 거기까지 ra, rra를 연산하는지?

		회전을 최적화 하기 위해서는 현재 이동시킬 원소의 위치와
		스택의 전체적인 크기를 알고 ra, rra 중 취사선택해야함
	
	*/
	size_t lst_size = ft_cir_dlstsize(ps_stat->stack_a);
	if (lst_size == 2)
	{
		sa(ps_stat);
		return (SUCCESS);
	}
	else if (lst_size == 3)
	{
		sort_3_elements(ps_stat);
		return (SUCCESS);
	}
	else if (lst_size <= 5)
	{
		sort_under5_elements(ps_stat);
		return (SUCCESS);
	}
	else// if (lst_size <= 100)
	{
		// sort_under5_elements(ps_stat);
		sort_under100_elements(ps_stat);
		return (SUCCESS);
	}
	return (SUCCESS);
}
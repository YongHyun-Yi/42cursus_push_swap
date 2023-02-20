/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_push_swap_solve.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:34:21 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/20 18:05:10 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_dlist *get_largest_node(t_dlist *my_stack)
{
	t_dlist *cur_node;
	t_dlist *max_node;

	cur_node = my_stack;
	max_node = cur_node;
	while (cur_node->next != my_stack)
	{
		cur_node = cur_node->next;
		if (cur_node->value > max_node->value)
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
		if (cur_node->value < min_node->value)
			min_node = cur_node;
	}
	return (min_node);
}

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
	if ((unsigned long long)rot_cnt > ft_cir_dlstsize(my_stack))
		rot_cnt = -1;
	else if ((unsigned long long)rot_cnt > ft_cir_dlstsize(my_stack) / 2)
		rot_cnt -= ft_cir_dlstsize(my_stack);
	// 정방향 회전과 역방향 회전 중 어느게 더 빠른지 계산한다
	ft_printf("rot cnt: %d\n", rot_cnt);
	return (rot_cnt);
}

long long	get_rotcnt_topos(t_dlist *my_stack, t_dlist *target_node)
{
	long long rot_cnt;
	t_dlist *cur_node;

	if (target_node->value < get_smallest_node(my_stack)->value) // 최솟값
		return (get_rotcnt_totop(my_stack, get_smallest_node(my_stack)));
	else if (target_node->value > get_largest_node(my_stack)->value) // 최댓값
		return (get_rotcnt_totop(my_stack, get_largest_node(my_stack)));
	rot_cnt = 0;
	cur_node = my_stack;
	while (!(target_node->value < cur_node->value && target_node->value > (cur_node->prev)->value)) // 사잇값
	{
		rot_cnt++;
		if (cur_node->next == my_stack)
			break ;
		cur_node = cur_node->next;
	}
	if ((unsigned long)rot_cnt > ft_cir_dlstsize(my_stack))
		rot_cnt = -1;
	else if ((unsigned long)rot_cnt > ft_cir_dlstsize(my_stack) / 2)
		rot_cnt -= ft_cir_dlstsize(my_stack);
	// 정방향 회전과 역방향 회전 중 어느게 더 빠른지 계산한다
	ft_printf("rot cnt: %d\n", rot_cnt);
	return (rot_cnt);
}

void	sort_under5_elements(t_ps_stat *ps_stat)
{
	while (ft_cir_dlstsize(ps_stat->stack_a) > 3)
	{
		pb(ps_stat);
		ft_printf("\ninitial push\n\n");
		print_all_my_stack(ps_stat);
	} // biggest sort 로 대체 가능성 있음
	
	if (!ft_is_stack_sorted(ps_stat->stack_a))
	{
		sort_3_elements(ps_stat);
		ft_printf("\n3 sort\n\n");
		print_all_my_stack(ps_stat);
	}
	
	if (ft_cir_dlstsize(ps_stat->stack_b) > 1 && (ps_stat->stack_b)->value < ((ps_stat->stack_b)->next)->value)
	{
		sb(ps_stat);
		ft_printf("\nswap b\n\n");
		print_all_my_stack(ps_stat);
	}
	// if (ft_cir_dlstsize(ps_stat->stack_b) > 1 && my_abs(get_rotcnt_topos(ps_stat->stack_a, ps_stat->stack_b)) >= my_abs(get_rotcnt_topos(ps_stat->stack_a, (ps_stat->stack_b)->next)) + 1)
	// 원소가 둘 이상이고 서로의 회전수를 비교해서 swap을 하는게 더 유리하다면 swap한다
	// 하지만 한번 push 하고나서 나머지의 회전수가 급격하게 바뀌는 케이스가 있다...
	// 그냥 간단하게 큰 값을 먼저 push하는 식으로 우선 타협
	// 4 2 5 3 1 -> sb 보다 rrr을 하고 나머지 작업을 수행하면 명령수가 하나 더 줄어든다

	// 여기선 get_rotcnt_topos가 ra, get_rotcnt_totop가 rb를 뜻하게 된다
	// 만약 둘다 0이아니라면
	// 둘다 양수라면 둘 중 하나라도 0이 될때까지 하나씩 줄이고 rr을 추가
	// 둘다 음수라면 둘 중 하나라도 0이 될때까지 하나씩 늘리고 rrr을 추가
	// r_cnt, rr_cnt가 필요, 해당 변수만큼 n_r, n_rr 을 호출

	while (ps_stat->stack_b) // stack_b의 헤더가 null 이 될때까지
	{
		n_ra(ps_stat, get_rotcnt_topos(ps_stat->stack_a, ps_stat->stack_b));
		pa(ps_stat);
		
		ft_printf("\nsorting...\n\n");
		print_all_my_stack(ps_stat);
	}
	// stack_b에 원소가 있는건 전체 원소수와 상관없나...?
	// stack_a에서의 적절한 위치찾아 넣는건 수가 많을때도 똑같지 않을까...?

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

	if (first < second && !(second < third))
	{
		rra(ps_stat);
		if (!(third < first))
			sa(ps_stat);
	}

	else if (second < third && third < first)
		ra(ps_stat);

	else
	{
		sa(ps_stat);
		if (!(second < third) && third < first)
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
		sa(ps_stat); // sa
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
	return (SUCCESS);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_push_swap_solve.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:34:21 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/23 10:12:49 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	dlist_valcmp(t_dlist *a, t_dlist *b)
{
	return (a->value < b->value);
}

t_dlist *get_largest_node(t_dlist *my_stack, int(*cmp)(t_dlist *, t_dlist *))
{
	t_dlist *cur_node;
	t_dlist *max_node;

	cur_node = my_stack;
	max_node = cur_node;
	while (cur_node->next != my_stack)
	{
		cur_node = cur_node->next;
		if (!cmp(cur_node, max_node))
			max_node = cur_node;
	}
	return (max_node);
}

t_dlist *get_smallest_node(t_dlist *my_stack, int(*cmp)(t_dlist *, t_dlist *))
{
	t_dlist *cur_node;
	t_dlist *min_node;

	cur_node = my_stack;
	min_node = cur_node;
	while (cur_node->next != my_stack)
	{
		cur_node = cur_node->next;
		if (cmp(cur_node, min_node))
			min_node = cur_node;
	}
	return (min_node);
}

// 비교하는 함수를 함수포인터로 비워두었다
// 나중에 dlist의 content에 무엇이 들어있고 그것을 어떻게 가공을해서 비교를 하던
// 그에 따라 비교하는 알고리즘을 가진 함수를 함수 포인터 부분에 넘겨주면
// 알아서 최댓값과 최솟값을 가진 노드를 반환해준다

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
	return (rot_cnt);
}

long long	get_rotcnt_topos(t_dlist *my_stack, t_dlist *target_node)
{
	long long rot_cnt;
	t_dlist *cur_node;

	if (target_node->value < get_smallest_node(my_stack, dlist_valcmp)->value) // 최솟값
		return (get_rotcnt_totop(my_stack, get_smallest_node(my_stack, dlist_valcmp)));
	else if (target_node->value > get_largest_node(my_stack, dlist_valcmp)->value) // 최댓값
		return (get_rotcnt_totop(my_stack, get_largest_node(my_stack, dlist_valcmp)));
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
		if (ft_cir_dlstsize(dest) - dest_rotcnt <= my_abs(dest_rotcnt) + my_abs(src_rotcnt))
			dest_rotcnt -= ft_cir_dlstsize(dest);
		else if (ft_cir_dlstsize(src) - src_rotcnt <= my_abs(dest_rotcnt) + my_abs(src_rotcnt))
			src_rotcnt -= ft_cir_dlstsize(src);
		// 반대 회전을 구해서 동시회전으로 돌리는 횟수가
		// 최선의 회전수를 합친것보다 이득이면 반대 회전수를 취한다
	}

	if (dest_rotcnt == src_rotcnt)
		return (dest_rotcnt);
		// 둘이 회전수가 같다면 둘중 하나로 반환한다
	
	if ((dest_rotcnt > 0) == (src_rotcnt > 0))
	{
		if (dest_rotcnt < src_rotcnt)
			dest_rotcnt *= -1;
		else
			src_rotcnt *= -1;
		return (dest_rotcnt + src_rotcnt);
		// 더 작은쪽의 부호를 반전시키고
		// 둘을 합하여 둘의 차이를 구한다
		// 최대 이만큼 동시 회전가능하다
		// 큰 쪽의 부호를 살리는 이유는 부호가 곧 방향이기 떄문
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
	double_rotcnt = get_double_rotcnt(dest, src, target_node);

	return (my_abs(dest_rotcnt) + my_abs(src_rotcnt) - my_abs(double_rotcnt));
	// 부호가 다르면 둘의 절댓값을 합친 횟수를 반환한다
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

	if (ft_cir_dlstsize(ps_stat->stack_b) > 1 && get_total_rotcnt(ps_stat->stack_a, ps_stat->stack_b, ps_stat->stack_b) >= get_total_rotcnt(ps_stat->stack_a, ps_stat->stack_b, (ps_stat->stack_b)->next))
	{
		if (get_double_rotcnt(ps_stat->stack_a, ps_stat->stack_b, (ps_stat->stack_b)->next))
		{
			n_rr(ps_stat, get_double_rotcnt(ps_stat->stack_a, ps_stat->stack_b, (ps_stat->stack_b)->next));
			ft_printf("double rotate\n\n");
			print_all_my_stack(ps_stat);
		}
	}

	while (ps_stat->stack_b) // stack_b의 헤더가 null 이 될때까지
	{
		n_ra(ps_stat, get_rotcnt_topos(ps_stat->stack_a, ps_stat->stack_b));
		pa(ps_stat);
		
		ft_printf("\nsorting...\n\n");
		print_all_my_stack(ps_stat);
	}
	// stack_b에 원소가 있는건 전체 원소수와 상관없나...?
	// stack_a에서의 적절한 위치찾아 넣는건 수가 많을때도 똑같지 않을까...?

	n_ra(ps_stat, get_rotcnt_totop(ps_stat->stack_a, get_smallest_node(ps_stat->stack_a, dlist_valcmp)));

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
	else if (lst_size <= 100)
	{
		sort_under100_elements(ps_stat);
		return (SUCCESS);
	}
	return (SUCCESS);
}


#include "push_swap.h"

void	sort_under5_elements(t_ps_stat *ps_stat)
{
	while (ft_cir_dlstsize(ps_stat->stack_a) > 3)
	{
		pb(ps_stat);
		ft_printf("\ninitial push\n\n");
		print_all_my_stack(ps_stat);
	}
	
	if (!ft_is_stack_sorted(ps_stat->stack_a))
	{
		sort_3_elements(ps_stat);
		ft_printf("\n3 sort\n\n");
		print_all_my_stack(ps_stat);
	}
	
	if (ft_cir_dlstsize(ps_stat->stack_b) == 2 && (ps_stat->stack_b)->value < ((ps_stat->stack_b)->next)->value)
	{
		sb(ps_stat);
		ft_printf("\nswap b\n\n");
		print_all_my_stack(ps_stat);
	}

	while (ps_stat->stack_b) // stack_b의 헤더가 null 이 될때까지
	{
		int rot_cnt = 0;
		t_dlist *cur_node = ps_stat->stack_a;
		while (1)
		{
			if (((ps_stat->stack_b)->value < cur_node->value && (ps_stat->stack_b)->value > (cur_node->prev)->value)) // 사잇값
				break ;
			if ((ps_stat->stack_b)->value < cur_node->value && (ps_stat->stack_b)->value < (cur_node->prev)->value && ft_is_stack_sorted(cur_node)) // 최솟값
				break ;
			if ((ps_stat->stack_b)->value > cur_node->value && (ps_stat->stack_b)->value > (cur_node->prev)->value && ft_is_stack_sorted(cur_node)) // 최댓값
				break ;
			// 최대 or 최소값일때 현재 노드 기준으로 정렬되어있으면 회전을 멈춘다
			rot_cnt++;
			if (cur_node->next == ps_stat->stack_a)
				break ;
			cur_node = cur_node->next;
		}
		if ((unsigned long)rot_cnt > ft_cir_dlstsize(ps_stat->stack_a))
			rot_cnt = -1;
		else if ((unsigned long)rot_cnt > ft_cir_dlstsize(ps_stat->stack_a) / 2)
			rot_cnt -= ft_cir_dlstsize(ps_stat->stack_a);
		// 정방향 회전과 역방향 회전 중 어느게 더 빠른지 계산한다
		ft_printf("rot cnt: %d", rot_cnt);
		while (rot_cnt)
		{
			if (rot_cnt > 0)
			{
				ra(ps_stat);
				rot_cnt--;
			}
			else
			{
				rra(ps_stat);
				rot_cnt++;
			}
		}
		pa(ps_stat);
		
		ft_printf("\nsorting...\n\n");
		print_all_my_stack(ps_stat);
	}
	// stack_b에 원소가 있는건 전체 원소수와 상관없나...?
	// stack_a에서의 적절한 위치찾아 넣는건 수가 많을때도 똑같지 않을까...?

	int last_rot_cnt = 0;
	t_dlist *last_cur_node = ps_stat->stack_a;
	while (!ft_is_stack_sorted(last_cur_node))
	{
		last_rot_cnt++;
		if (last_cur_node->next == ps_stat->stack_a)
			break ;
		last_cur_node = last_cur_node->next;
	}
	if ((unsigned long)last_rot_cnt > ft_cir_dlstsize(ps_stat->stack_a))
		last_rot_cnt = -1;
	else if ((unsigned long)last_rot_cnt > ft_cir_dlstsize(ps_stat->stack_a) / 2)
		last_rot_cnt -= ft_cir_dlstsize(ps_stat->stack_a);
	
	while (last_rot_cnt)
	{
		if (last_rot_cnt > 0)
		{
			ra(ps_stat);
			last_rot_cnt--;
		}
		else
		{
			rra(ps_stat);
			last_rot_cnt++;
		}
	}

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
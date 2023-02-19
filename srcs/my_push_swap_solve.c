

#include "push_swap.h"

// void	sort_under5_elements(t_ps_stat *ps_stat)
// {
// 	t_dlist *my_stack;

// 	my_push(ps_stat->stack_b, ps_stat->stack_a);
// 	my_push(ps_stat->stack_b, ps_stat->stack_a);
// 	sort_3_elements(ps_stat);
// 	my_stack = ps_stat->stack_b;
// }

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
		my_reverse_rotate(&ps_stat->stack_a); // rra
		if (!(third < first))
			my_swap(ps_stat->stack_a); // sa
	}
	else if (!(first < second) && !(second < third) && third < first)
	{
		my_swap(ps_stat->stack_a); // sa
		my_reverse_rotate(&ps_stat->stack_a); // rra
	}
	else if (!(first < second) && second < third && !(third < first))
		my_swap(ps_stat->stack_a); // sa
	else if (!(first < second) && second < third && third < first)
		my_rotate(&ps_stat->stack_a); // ra
	
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
		my_swap(ps_stat->stack_a); // sa
		return (SUCCESS);
	}
	else if (lst_size == 3)
	{
		sort_3_elements(ps_stat);
		return (SUCCESS);
	}
	return (SUCCESS);
}
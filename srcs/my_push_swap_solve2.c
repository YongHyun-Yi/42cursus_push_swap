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

	t_list *cur_node;
	t_list *cmp_node;
	char *cur_inst;
	char *cmp_inst;

	cur_node = inst_lst;
	cur_inst = (char *)(cur_node->content);
	while (cur_node->next)
	{
		cmp_node = cur_node->next;
		while(cmp_node->next != NULL)
		{
			cmp_inst = (char *)(cmp_node->content);
			if (cur_inst[0] != cmp_inst[0] || (cur_inst[0] == 'p' || cmp_inst[0] == 'p') || ft_strnstr(cur_inst, cmp_inst, 3))
				break ;
			// 전혀 다른종류의 명령어이거나 or push 명령어이거나 or 완전 같은 명령어이거나

			if (cur_inst[0] == 's' && (!ft_strnstr(cur_inst, "ss\n", 3) && !ft_strnstr(cmp_inst, "ss\n", 3)) && cur_inst[1] != cmp_inst[1]) // sa sb
			{
				cur_node->content = "ss\n";
				cmp_node->content = "";
				break ;
			}
			else // r? r?
			{
				if ((ft_strnstr(cur_inst, "ra\n", 3) && ft_strnstr(cmp_inst, "rb\n", 3)) || (ft_strnstr(cur_inst, "rb\n", 3) && ft_strnstr(cmp_inst, "ra\n", 3)))
				{
					cur_node->content = "rr\n";
					cmp_node->content = "";
					break ;
				}
				if ((ft_strnstr(cur_inst, "rra\n", 3) && ft_strnstr(cmp_inst, "rrb\n", 3)) || (ft_strnstr(cur_inst, "rrb\n", 3) && ft_strnstr(cmp_inst, "rra\n", 3)))
				{
					cur_node->content = "rrr\n";
					cmp_node->content = "";
					break ;
				}
				if ((ft_strnstr(cur_inst, "rr\n", 3) && ft_strnstr(cmp_inst, "rra\n", 3)) || (ft_strnstr(cur_inst, "rra\n", 3) && ft_strnstr(cmp_inst, "rr\n", 3)))
				{
					cur_node->content = "rb\n";
					cmp_node->content = "";
					break ;
				}
				if ((ft_strnstr(cur_inst, "rr\n", 3) && ft_strnstr(cmp_inst, "rrb\n", 3)) || (ft_strnstr(cur_inst, "rrb\n", 3) && ft_strnstr(cmp_inst, "rr\n", 3)))
				{
					cur_node->content = "ra\n";
					cmp_node->content = "";
					break ;
				}
				if ((ft_strnstr(cur_inst, "rrr\n", 3) && ft_strnstr(cmp_inst, "ra\n", 3)) || (ft_strnstr(cur_inst, "ra\n", 3) && ft_strnstr(cmp_inst, "rrr\n", 3)))
				{
					cur_node->content = "rrb\n";
					cmp_node->content = "";
					break ;
				}
				if ((ft_strnstr(cur_inst, "rrr\n", 3) && ft_strnstr(cmp_inst, "rb\n", 3)) || (ft_strnstr(cur_inst, "rb\n", 3) && ft_strnstr(cmp_inst, "rrr\n", 3)))
				{
					cur_node->content = "rra\n";
					cmp_node->content = "";
					break ;
				}
				// if (cur_inst[1] != cmp_inst[1])  // r! r!
				// {
				// 	if (cur_inst[2] == cmp_inst[2]) // ra\n rb\n || rb\n ra\n
				// 	{
				// 		cur_node->content = "rr\n";
				// 		cmp_node->content = "";
				// 		break ;
				// 	}
				// 	else if (cur_inst[1] == cmp_inst[2] || cur_inst[2] == cmp_inst[1]) // ra rra, rra ra || rb rrb, rrb rb
				// 	{
				// 		cur_node->content = "";
				// 		cmp_node->content = "";
				// 		break ;
				// 	}
				// }
				// else if (cur_inst[2] != cmp_inst[2]) // rr! rr!
				// {
				// 	if (cur_inst[2] != '\n' && cmp_inst[2] != '\n') // rra rrb
				// 	{
				// 		cur_node->content = "rrr\n";
				// 		cmp_node->content = "";
				// 		break ;
				// 	}
				// 	else if (cur_inst[2] == 'a' || cmp_inst[2] == 'a') // rr rra
				// 	{
				// 		cur_node->content = "rrb\n";
				// 		cmp_node->content = "";
				// 		break ;
				// 	}
				// 	else // rr rrb || rrb rr
				// 	{
				// 		cur_node->content = "rra\n";
				// 		cmp_node->content = "";
				// 		break ;
				// 	}
				// }
				// else // rrr
				// {
				// 	if (cur_inst[1] == 'a' || cmp_inst[1] == 'a') // rrr ra || ra rrr
				// 	{
				// 		cur_node->content = "rrb\n";
				// 		cmp_node->content = "";
				// 		break ;
				// 	}
				// 	else // rrr rb || rb rrr
				// 	{
				// 		cur_node->content = "rra\n";
				// 		cmp_node->content = "";
				// 		break ;
				// 	}
				// }
			}
			cmp_node = cmp_node->next;
		}
		cur_node = cur_node->next;
		cur_inst = (char *)(cmp_node->content);
	}
	return ;
}

int	ft_cir_dlst_hasval(t_dlist *my_dlst, int val)
{
	t_dlist	*cur_node;

	if (!my_dlst)
		return (0);
	cur_node = my_dlst;
	while (1)
	{
		if (cur_node->value == val)
			return (1);
		if (cur_node->next == my_dlst)
			return (0);
		cur_node = cur_node->next;
	}
}

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
		if (cur_idx == (size_t)idx_cmp_node->value)
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
	t_dlist *idx_list;
	t_dlist *cur_node;
	t_dlist *new;

	idx_list = NULL;
	cur_node = my_stack;
	while (1)
	{
		new = ft_dlstnew(get_lis_idx(cur_node, idx_list));
		if (!new)
			return (FAIL);
		ft_cir_dlstadd_back(&idx_list, new);
		if (cur_node->next == my_stack)
			break ;
		cur_node = cur_node->next;
	}
	return (idx_list);
}

t_dlist *get_lis_list(t_dlist *my_stack)
{
	t_dlist *idx_list;
	t_dlist *lis_list;
	size_t	cur_idx;
	t_dlist *cur_node;
	t_dlist *new;

	idx_list = get_lis_idx_list(my_stack);
	lis_list = NULL;
	cur_idx = get_largest_node(idx_list)->value;
	cur_node = my_stack->prev;
	idx_list = idx_list->prev;
	while (1)
	{
		if ((size_t)idx_list->value == cur_idx)
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
	return (lis_list);
}
// instructions optimizing

// b_to_a
// get leastrot node -> pa

// a_to_b
// if in LIS -> ra
// else -> pb
// if less than pivot -> rb

t_dlist *get_leastrot_nonlis_node(t_dlist *src, t_dlist *lis_list)
{
	t_dlist *cur_node;
	t_dlist *least_node;
	
	cur_node = src;
	least_node = NULL;
	while (cur_node->next != src)
	{
		cur_node = cur_node->next;
		if (!ft_cir_dlst_hasval(lis_list, cur_node->value))
		{
			if (least_node == NULL)
				least_node = cur_node;
			else if (dlist_rotcmp2(src, cur_node, least_node)) // 오직 totop이 가장작은애만
				least_node = cur_node;
		}
	}
	return (least_node);
}

void	b_to_a(t_ps_stat *ps_stat)
{
	while (ps_stat->stack_b) // stack_b의 헤더가 null 이 될때까지
	{
		t_dlist *target_node;

		target_node = get_leastrot_node(ps_stat->stack_a, ps_stat->stack_b);
		n_rr(ps_stat, get_double_rotcnt(ps_stat->stack_a, ps_stat->stack_b, target_node));
		n_ra(ps_stat, get_rotcnt_topos(ps_stat->stack_a, target_node));
		n_rb(ps_stat, get_rotcnt_totop(ps_stat->stack_b, target_node));
		pa(ps_stat);
		
		ft_printf("\nb to a...\n\n");
		print_all_my_stack(ps_stat);
	}
	n_ra(ps_stat, get_rotcnt_totop(ps_stat->stack_a, get_smallest_node(ps_stat->stack_a)));
}

void	a_to_b(t_ps_stat *ps_stat, t_dlist *lis_list, int pivot)
{
	t_dlist *target_node;

	while (1)
	{
		target_node = get_leastrot_nonlis_node(ps_stat->stack_a, lis_list);
		if (!target_node)
			return ;
		// n_rr(ps_stat, get_double_rotcnt(ps_stat->stack_b, ps_stat->stack_a, target_node));
		// n_rb(ps_stat, get_rotcnt_topos(ps_stat->stack_b, target_node));
		n_ra(ps_stat, get_rotcnt_totop(ps_stat->stack_a, target_node));
		
		pb(ps_stat);

		// pivot에 따라 분기, 사이즈가 1이거나 같은 청크끼리 붙어잇으면 패스
		if (ft_cir_dlstsize(ps_stat->stack_b) > 1 && target_node->value < pivot && (target_node->next)->value >= pivot)
			rb(ps_stat);

		ft_printf("\na to b...\n\n");
		print_all_my_stack(ps_stat);
	}
}

int	get_pivot(t_dlist *my_stack)
{
	int min_val;
	int max_val;

	min_val = get_smallest_node(my_stack)->value;
	max_val = get_largest_node(my_stack)->value;
	return ((min_val + max_val) / 2);
}

void	sort_under100_elements(t_ps_stat *ps_stat)
{
	t_dlist *lis_list;
	lis_list = get_lis_list(ps_stat->stack_a);
	ft_printf("lis ptr: %p\n", lis_list);
	int	pivot;
	pivot = get_pivot(ps_stat->stack_a);
	ft_printf("pivot: %d\n", pivot);
	a_to_b(ps_stat, lis_list, pivot);
	b_to_a(ps_stat);
	return ;

	// LIS를 구하는 함수
	// pivot을 구하는 함수 구현
	
	// get_leastrot_node를 수정해서 조건에 LIS가 아닌 노드만 그리디로 a에서 b로 보냄
	// pivot에 따라 chunk를 나눔 pa후 rb할지 결정

	// get_leastrot_node로 그리디로 b에서 a로 보냄

	// 명령어 최적화
}
//
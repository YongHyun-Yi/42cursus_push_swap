/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:48:27 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/27 21:00:32 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_my_stack(t_dlist *my_stack)
{
	t_dlist *cur_node;

	cur_node = my_stack;
	while (cur_node)
	{
		ft_printf("%d ", cur_node->value);
		if (cur_node->next == my_stack)
			break ;
		cur_node = cur_node->next;
	}
	ft_printf("\n");
	return ;
}

// void	print_all_my_stack(t_ps_stat *ps_stat)
// {
// 	ft_printf("\n");
// 	ft_printf("======== << print stack >> ========\n");
// 	ft_printf("\n");
// 	ft_printf("stack a: ");
// 	print_my_stack(ps_stat->stack_a);
// 	ft_printf("stack b: ");
// 	print_my_stack(ps_stat->stack_b);
// 	ft_printf("\n");
// 	ft_printf("===================================\n");
// 	ft_printf("\n");

// 	return ;
// }

void 	my_exit(t_ps_stat *ps_stat, int no_err)
{
	// ft_printf("bit array ptr: %p\n",ps_stat->bit_array);
	// ft_printf("split argv ptr: %p\n",ps_stat->split_argv);
	// ft_printf("stack_a ptr: %p\n",ps_stat->stack_a);
	// ft_printf("stack_b ptr: %p\n",ps_stat->stack_b);
	// ft_printf("inst lst ptr: %p\n",ps_stat->inst_lst);
	if (ps_stat->bit_array)
	{
		free(ps_stat->bit_array);
		ps_stat->bit_array = NULL;
	}
	if (ps_stat->split_argv)
	{
		free(ps_stat->split_argv);
		ps_stat->split_argv = NULL;
	}
	if (ps_stat->stack_a)
		ft_cir_dlstclear(&ps_stat->stack_a);
	if (ps_stat->stack_b)
		ft_cir_dlstclear(&ps_stat->stack_b);
	if (ps_stat->inst_lst)
		ft_lstclear(&ps_stat->inst_lst, NULL);
	// ft_printf("--------------------------------------\n");
	// ft_printf("bit array ptr: %p\n",ps_stat->bit_array);
	// ft_printf("split argv ptr: %p\n",ps_stat->split_argv);
	// ft_printf("stack_a ptr: %p\n",ps_stat->stack_a);
	// ft_printf("stack_b ptr: %p\n",ps_stat->stack_b);
	// ft_printf("inst lst ptr: %p\n",ps_stat->inst_lst);
	if (no_err)
		exit(EXIT_SUCCESS);
	ft_putstr_fd("Error\n", 2);
	exit(EXIT_FAILURE);
}

void	print_inst_lst(void *str)
{
	ft_printf("%s\n", str);
}

int ft_is_stack_sorted(t_dlist *my_stack)
{
	t_dlist	*cur_node;

	if (!my_stack)
		return (FAIL);
	cur_node = my_stack;
	while (cur_node->next != my_stack) // 다음 노드가 헤더라면, 마지막 노드까지 왔다 즉, 문제없이 한 바퀴 돌았다면 끝
	{
		if (!ft_value_cmp(cur_node, cur_node->next)) // 다음 노드보다 값이 크면 즉, 오름차순이 아니면
			return (FAIL);
		cur_node = cur_node->next;
	}
	return (SUCCESS);
}

void	push_swap_parsing(t_ps_stat *ps_stat, char *argv[]) // staic function
{
	t_dlist	*new_node;
	size_t	s_idx;

	ps_stat->bit_array = ft_calloc((UINT_MAX / 8) + 1, sizeof(char));
	while (*argv)
	{
		ps_stat->split_argv = ft_split(*argv, ' ');
		s_idx = 0;
		while ((ps_stat->split_argv)[s_idx])
		{
			if (!ft_strisint((ps_stat->split_argv)[s_idx]))
				my_exit(ps_stat, FAIL);
			if (!ft_check_intdup(ps_stat->bit_array, ft_atoi((ps_stat->split_argv)[s_idx])))
				my_exit(ps_stat, FAIL);
			new_node = ft_dlstnew(ft_atoi((ps_stat->split_argv)[s_idx]));
			if (!new_node)
				my_exit(ps_stat, FAIL);
			ft_cir_dlstadd_back(&ps_stat->stack_a, new_node);
			s_idx++;
		}
		free(ps_stat->split_argv);
		ps_stat->split_argv = NULL;
		argv++;
	}
	free(ps_stat->bit_array);
	ps_stat->bit_array = NULL;
}

int main(int argc, char *argv[])
{
	t_ps_stat ps_stat;

	if (argc < 2)
		return (0);
	ft_bzero(&ps_stat, sizeof(t_ps_stat));
	push_swap_parsing(&ps_stat, argv + 1);
	if (ft_is_stack_sorted(ps_stat.stack_a) && ps_stat.stack_b == NULL)
		return (EXIT_SUCCESS);

	// ft_printf("inputs: ");
	// print_my_stack(ps_stat.stack_a);
	
	my_push_swap_solve(&ps_stat);

	// inst_lst_optimizing(ps_stat->inst_lst); // 뭔가 문제있음

	ft_lstiter(ps_stat.inst_lst, print_inst_lst);

	// system("leaks push_swap");

	my_exit(&ps_stat, SUCCESS);
}

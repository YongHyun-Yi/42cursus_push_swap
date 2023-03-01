/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 00:22:43 by yonghyle          #+#    #+#             */
/*   Updated: 2023/03/02 00:43:16 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

static void	free_splits(char **splits)
{
	char	*cur_split;
	char	**next_split;

	cur_split = *splits;
	next_split = splits + 1;
	while (cur_split)
	{
		free(cur_split);
		cur_split = *next_split;
		++next_split;
	}
	free(splits);
}

void	get_valid_argv(t_ps_stat *ps_stat, char **split_argv)
{
	t_dlist	*new_node;

	while (split_argv)
	{
		if (!ft_strisint(*split_argv) || !ft_check_intdup(ps_stat->bit_array,
				ft_atoi(*split_argv)))
			my_exit(ps_stat, FAIL);
		new_node = ft_dlstnew(ft_atoi(*split_argv));
		if (!new_node)
			my_exit(ps_stat, FAIL);
		ft_cir_dlstadd_back(&ps_stat->stack_a, new_node);
		++split_argv;
	}
}

static void	push_swap_parsing(t_ps_stat *ps_stat, char *argv[])
{
	size_t	s_idx;

	ps_stat->bit_array = ft_calloc((UINT_MAX / 8) + 1, sizeof(char));
	while (*argv)
	{
		ps_stat->split_argv = ft_split(*argv, ' ');
		s_idx = 0;
		get_valid_argv(ps_stat, ps_stat->split_argv);
		free_splits(ps_stat->split_argv);
		argv++;
	}
	free(ps_stat->bit_array);
	ps_stat->split_argv = NULL;
	ps_stat->bit_array = NULL;
}

void	set_ps_func_arr(void (*func_arr[])(t_ps_stat *))
{
	func_arr[0] = sa;
	func_arr[1] = sb;
	func_arr[2] = ss;
	func_arr[3] = pa;
	func_arr[4] = pb;
	func_arr[5] = ra;
	func_arr[6] = rb;
	func_arr[7] = rr;
	func_arr[8] = rra;
	func_arr[9] = rrb;
	func_arr[10] = rrr;
}

void	set_ps_str_arr(char *str_arr[])
{
	str_arr[0] = "sa\n";
	str_arr[1] = "sb\n";
	str_arr[2] = "ss\n";
	str_arr[3] = "pa\n";
	str_arr[4] = "pb\n";
	str_arr[5] = "ra\n";
	str_arr[6] = "rb\n";
	str_arr[7] = "rr\n";
	str_arr[8] = "rra\n";
	str_arr[9] = "rrb\n";
	str_arr[10] = "rrr\n";
}

void	my_push_swap_checker(t_ps_stat	*ps_stat)
{
	char	*inst;
	size_t	idx;

	*inst = get_next_line(STDIN_FILENO);
	while (inst)
	{
		idx = 0;
		while (1)
		{
			if (ft_strncmp(inst, ps_stat->str_arr[idx], 3) == 0)
			{
				ps_stat->func_arr[idx](&ps_stat);
				free(inst);
				break ;
			}
			idx++;
			if (idx == 11)
			{
				ft_printf("inst : %s\n", inst);
				ft_printf("Can't find instructions\n");
				free(inst);
				my_exit(&ps_stat, FAIL);
			}
		}
		inst = get_next_line(STDIN_FILENO);
	}
	if (ft_is_stack_sorted(ps_stat->stack_a) && ps_stat->stack_b == NULL)
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	my_exit(ps_stat, SUCCESS);
}

int main(int argc, char *argv[])
{
	t_ps_stat	ps_stat;

	if (argc < 2)
		return (0);
	ft_bzero(&ps_stat, sizeof(t_ps_stat));
	push_swap_parsing(&ps_stat, argv + 1);
	set_ps_func_arr(ps_stat.func_arr);
	set_ps_str_arr(ps_stat.str_arr);
	my_push_swap_checker(&ps_stat);
}

// 모든 명령어를 다 입력받고나서 에러처리를 할 필요는 없음
// 잘못된 명령어를 입력하면 즉시 Error 를 출력함 (공백포함)
// 인자가 없으면 즉시 종료
// eof까지는 입력받은 명령어를 즉시 수행하는듯함
// 비어있는 스택에 대한 명령어는 입력은 들어가도 아무 행동을 하지 않는듯
// 비어있는 스택에 명령을 사용한다고 해서 오류가 발생하진 않음
//
// checker만 동작하면 잘 작동한다
// 하지만 pipe를 통해 값을 받으면 segfault 발생 어째서...?
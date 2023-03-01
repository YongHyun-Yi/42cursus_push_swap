/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 00:22:43 by yonghyle          #+#    #+#             */
/*   Updated: 2023/03/02 04:50:12 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	free_splits(char **splits)
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

	while (*split_argv)
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

void	my_push_swap_checker(t_ps_stat	*ps_stat)
{
	char	*inst;
	size_t	idx;

	inst = get_next_line(STDIN_FILENO);
	while (inst)
	{
		idx = 0;
		while (ft_strncmp(inst, ps_stat->str_arr[idx], 3) != 0)
		{
			if (idx == 11)
			{
				free(inst);
				my_exit(ps_stat, FAIL);
			}
			idx++;
		}
		ps_stat->func_arr[idx](ps_stat);
		free(inst);
		inst = get_next_line(STDIN_FILENO);
	}
	if (ft_is_stack_sorted(ps_stat->stack_a) && ps_stat->stack_b == NULL)
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	my_exit(ps_stat, SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_ps_stat	ps_stat;

	if (argc < 2)
		return (0);
	ft_bzero(&ps_stat, sizeof(t_ps_stat));
	set_ps_func_arr(ps_stat.func_arr);
	set_ps_str_arr(ps_stat.str_arr);
	push_swap_parsing(&ps_stat, argv + 1);
	my_push_swap_checker(&ps_stat);
}

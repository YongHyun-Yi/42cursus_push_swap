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

static int	get_valid_argv(t_ps_stat *ps_stat, char	*bit_arr, char **split_argv)
{
	t_dlist	*new_node;
	char	**argv_ptr;

	argv_ptr = split_argv;
	while (*argv_ptr)
	{
		if (!ft_strisint(*argv_ptr) || !ft_check_intdup(bit_arr,
				ft_atoi(*argv_ptr)))
		{
			free_splits(split_argv);
			return (FAIL);
		}
		new_node = ft_dlstnew(ft_atoi(*argv_ptr));
		if (!new_node)
		{
			free_splits(split_argv);
			return (FAIL);
		}
		ft_cir_dlstadd_back(&ps_stat->stack_a, new_node);
		++argv_ptr;
	}
	free_splits(split_argv);
	return (SUCCESS);
}

static int	push_swap_parsing(t_ps_stat *ps_stat, char *argv[])
{
	char	*bit_array;
	char	**split_argv;

	bit_array = ft_calloc((UINT_MAX / 8) + 1, sizeof(char));
	while (*argv)
	{
		split_argv = ft_split(*argv, ' ');
		if (!split_argv || !get_valid_argv(ps_stat, bit_array, split_argv))
		{
			free(bit_array);
			return (FAIL);
		}
		argv++;
	}
	free(bit_array);
	return (SUCCESS);
}

void	my_push_swap_checker(t_ps_stat	*ps_stat)
{
	char	*inst;
	size_t	idx;

	inst = get_next_line(STDIN_FILENO);
	while (inst)
	{
		idx = 0;
		while (ft_strlen(inst) != ft_strlen(ps_stat->str_arr[idx])
			|| ft_strncmp(inst, ps_stat->str_arr[idx], ft_strlen(inst)) != 0)
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
}

int	main(int argc, char *argv[])
{
	t_ps_stat	ps_stat;

	if (argc < 2)
		return (0);
	ft_bzero(&ps_stat, sizeof(t_ps_stat));
	set_ps_func_arr(ps_stat.func_arr);
	set_ps_str_arr(ps_stat.str_arr);
	if (!push_swap_parsing(&ps_stat, argv + 1))
		my_exit(&ps_stat, FAIL);
	my_push_swap_checker(&ps_stat);
	my_exit(&ps_stat, SUCCESS);
}

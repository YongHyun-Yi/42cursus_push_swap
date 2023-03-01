/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:48:27 by yonghyle          #+#    #+#             */
/*   Updated: 2023/03/02 00:41:33 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	print_inst_lst(void *str)
{
	ft_printf("%s", str);
}

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

static void	get_valid_argv(t_ps_stat *ps_stat, char **split_argv)
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

int	main(int argc, char *argv[])
{
	t_ps_stat	ps_stat;

	if (argc < 2)
		return (0);
	ft_bzero(&ps_stat, sizeof(t_ps_stat));
	push_swap_parsing(&ps_stat, argv + 1);
	if (ft_is_stack_sorted(ps_stat.stack_a) && ps_stat.stack_b == NULL)
		my_exit(&ps_stat, SUCCESS);
	my_push_swap_solve(&ps_stat);
	ft_lstiter(ps_stat.inst_lst, print_inst_lst);
	my_exit(&ps_stat, SUCCESS);
}

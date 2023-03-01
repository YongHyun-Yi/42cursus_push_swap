

#include "push_swap_bonus.h"

void 	my_exit(t_ps_stat *ps_stat, int no_err)
{
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
	if (no_err)
		exit(EXIT_SUCCESS);
	ft_putstr_fd("Error\n", 2);
	exit(EXIT_FAILURE);
}

int ft_is_stack_sorted(t_dlist *my_stack)
{
	t_dlist	*cur_node;

	if (!my_stack)
		return (FAIL);
	cur_node = my_stack;
	while (cur_node->next != my_stack)
	{
		if (!ft_value_cmp(cur_node, cur_node->next))
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
	str_arr[6] = "rb\n"; // 세그폴트 발생
	str_arr[7] = "rr\n"; // 세그폴트 발생
	str_arr[8] = "rra\n";
	str_arr[9] = "rrb\n"; // 세그폴트 발생
	str_arr[10] = "rrr\n"; // 세그폴트 발생
}

int main(int argc, char *argv[])
{
	t_ps_stat ps_stat;
	void (*func_arr[11])(t_ps_stat *);
	char *str_arr[11];

	if (argc < 2)
		return (0);
	ft_bzero(&ps_stat, sizeof(t_ps_stat));
	push_swap_parsing(&ps_stat, argv + 1);

	set_ps_func_arr(func_arr);
	set_ps_str_arr(str_arr);

	char *inst = get_next_line(STDIN_FILENO);
	int cnt = 1;
	while (inst)
	{
		// 명령어를 문자열 배열에서 찾기
		// 찾은 문자열의 인덱스로 함수포인터 배열 실행
		// 못찾았다면 my_exit 호출
		// ft_printf("inst : %s", inst); // << 이거 없으면 출력 이상하게 들어옴;
		int idx = 0;
		while (1)
		{
			// ft_printf("inst : %s", inst);
			if (ft_strncmp(inst, str_arr[idx], 3) == 0)
			{
				func_arr[idx](&ps_stat);
				free(inst);
				break ;
			}
			idx++;
			if (idx == 11)
			{
				ft_printf("cnt : %d\n", cnt);
				ft_printf("inst : %s\n", inst);
				ft_printf("inst : %d\n", *inst);
				ft_printf("Can't find instructions\n");
				free(inst);
				my_exit(&ps_stat, FAIL);
			}
			// ft_printf("inst : %s", inst);
		}
		inst = get_next_line(STDIN_FILENO);
		cnt++;
	}
	if (ft_is_stack_sorted(ps_stat.stack_a) && ps_stat.stack_b == NULL)
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	my_exit(&ps_stat, SUCCESS);
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
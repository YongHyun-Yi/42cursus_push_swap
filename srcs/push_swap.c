/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:48:27 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/10 09:21:23 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

int	ft_isnum(char *str, int (*f)(int))
{
	while (*str)
	{
		if (!f(*str++))
			return (FAIL);
	}
	return (SUCCESS);
}

int	ft_isnumint(char *str)
{
	int	is_postive;
	int	has_sign;

	is_postive = 1;
	has_sign = 0;
	if (str[0] == '-' || str[0] == '+')
	{
		is_postive -= (str[0] == '-');
		has_sign = 1;
	}
	// 부호 처리

	if (!ft_isnum(str + has_sign, ft_isdigit))
	{
		ft_printf("<<< There wrong arguments >>>\n");
		return (FAIL);
	}
	// 정수 이외문자 처리

	if (ft_strlen(str + has_sign) > 10)
	{
		ft_printf("<<< Arguments overflow >>>\n");
		return (FAIL);
	}
	else if (ft_strlen(str + has_sign) == 10)
	{
		if ((str + has_sign)[0] > '2')
		{
			ft_printf("<<< Arguments overflow >>>\n");
			return (FAIL);
		}
	}
	// 자릿수 및 첫자리수 처리

	if ((ft_atoi(str) >= 0) != is_postive)
	{
		ft_printf("<<< Arguments overflow >>>\n");
		return (FAIL);
	}
	return (SUCCESS);
	// overflow로 인한 부호 변화 처리
}

int	is_argv_dup(char *bit_masking, unsigned int num)
{
	// char *bit_masking = ft_calloc(UINT_MAX / 8, sizeof(char)); // calloc에서 꽤나 시간이 걸림...

	int	div = num / 8;
	int mod = num % 8;

	if (*(bit_masking + div) & (1 << mod))
	{
		ft_printf("<<< (%d) already exist in array >>>\n", num);
		return (FAIL);
	}

	*(bit_masking + div) = (*(bit_masking + div) | (1 << mod));
	ft_printf("(%d) add to array \n", num);
	return (SUCCESS);
}

void parse_test(int argc, char *argv[])
{
	ft_printf("total argc: %d\n", argc);
	
	ft_printf("===============================\n");
	
	for (int i = 1; i < argc; i++)
		ft_printf("argv[%d]: %s\n", i, argv[i]);
	
	ft_printf("===============================\n");

	t_ft_list *stack_a = NULL;
	char *bit_masking = ft_calloc((UINT_MAX / 8), sizeof(char));

	for (int i = 1; i < argc; i++)
	{
		char **split_argv = ft_split(argv[i], ' ');

		while (*split_argv)
		{
			ft_printf("cur str: %s\n", *split_argv);

			if (!ft_isnumint(*split_argv))
				exit(EXIT_FAILURE);
			
			int num = ft_atoi(*split_argv);
			
			if (!is_argv_dup(bit_masking, num))
				exit(EXIT_FAILURE);

			t_ft_list *cur_node = stack_a;
			while (stack_a && cur_node->next)
				cur_node = cur_node->next;

			t_ft_list *new_node = (t_ft_list *)malloc(sizeof(t_ft_list));
			new_node->val = num;
			new_node->next = NULL;

			if (cur_node)
				cur_node->next = new_node;
			else
				stack_a = new_node;
			
			split_argv++;
		}
		
	}

	t_ft_list *print_node = stack_a;
	int i = 0;
	while (print_node)
	{
		ft_printf("stack_a[%d]: %d\n", i++, print_node->val);
		print_node = print_node->next;
	}
}

int main(int argc, char *argv[])
{
	if (argc < 2)
		exit(0);
	
	parse_test(argc, argv);

	///////////// 비트 마스킹 간단 실습 /////////////////
	
	// char *bit_masking = ft_calloc(1, sizeof(char)); // -> char : 1byte = 8bit ->> 8개의 요소에 대해서 중복체크 가능?

	// int num = 4;
	
	// *bit_masking = *bit_masking | (1 << num);

	// if (*bit_masking & (1 << num))
	// 	ft_printf("This bit array has %d\n", num);

	///////////////////////////////////////////////

	// ft_putstr_fd("Error\n", 2); // 에러는 stderr로 출력해야 한다
	// exit(EXIT_FAILURE);
}

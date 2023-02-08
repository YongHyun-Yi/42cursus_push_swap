/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:48:27 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/08 14:46:04 by yonghyle         ###   ########.fr       */
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
	int		is_postive;

	is_postive = 1;
	if (str[0] == '-' || str[0] == '+')
	{
		is_postive -= (str[0] == '-');
		str++;
	}
	// 부호 처리

	if (!ft_isnum(str, ft_isdigit))
		return (FAIL);
	// 정수 이외문자 처리

	if (ft_strlen(str) > 10)
		return (FAIL);
	else if (ft_strlen(str) == 10)
		if (str[0] > '2')
			return (FAIL);
	// 자릿수 및 첫자리수 처리

	if ((ft_atoi(str) >= 0) != is_postive)
		return (FAIL);
	return (SUCCESS);
	// overflow로 인한 부호 변화 처리
}

int main(int argc, char *argv[])
{
	if (argc < 2)
		exit(0);
	
	ft_printf("total argc: %d\n", argc);
	
	ft_printf("===============================\n");
	
	for (int i = 1; i < argc; i++)
		ft_printf("argv[%d]: %s\n", i, argv[i]);
	
	ft_printf("===============================\n");

	t_ft_list *stack_a = NULL;

	for (int i = 1; i < argc; i++)
	{
		if (!ft_isnumint(argv[i]))
			exit(EXIT_FAILURE);

		t_ft_list *cur_node = stack_a;
		while (stack_a && cur_node->next)
			cur_node = cur_node->next;

		t_ft_list *new_node = (t_ft_list *)malloc(sizeof(t_ft_list));
		new_node->val = ft_atoi(argv[i]);
		new_node->next = NULL;

		if (cur_node)
			cur_node->next = new_node;
		else
			stack_a = new_node;
	}

	t_ft_list *print_node = stack_a;
	int i = 0;
	while (print_node)
	{
		ft_printf("stack_a[%d]: %d\n", i++, print_node->val);
		print_node = print_node->next;
	}

	ft_printf("===============================\n");

	ft_printf("test const macro [SUCCESS]: %d\n", SUCCESS);
	ft_printf("test const macro [FAIL]: %d\n", FAIL);

	ft_printf("===============================\n");

	ft_printf("test exit function\n");
	ft_printf("\n");
	ft_printf("Could you see this messege?\n");
	ft_putstr_fd("Error\n", 2); // 에러는 stderr로 출력해야 한다
	exit(EXIT_FAILURE);
	ft_printf("Than, How about now?\n");
}

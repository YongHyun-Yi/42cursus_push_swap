/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:48:27 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/07 10:41:59 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

int main()
{
	t_ft_list *iter;
	t_ft_list *head1;
	t_ft_list *node1 = (t_ft_list *)malloc(sizeof(t_ft_list));
	t_ft_list *node2 = (t_ft_list *)malloc(sizeof(t_ft_list));
	head1 = node1;
	node1->val = 1;
	node1->next = node2;
	node2->val = 2;
	node2->next = NULL;

	printf("head1: ");
	iter = head1;
	while (iter)
	{
		printf("%d ", iter->val);
		iter = iter->next;
	}
	printf("\n");

	ft_printf("\n<< SWAP A >>\n\n");
	swap_a(&head1);

	printf("head1: ");
	iter = head1;
	while (iter)
	{
		printf("%d ", iter->val);
		iter = iter->next;
	}
	printf("\n");

	printf("------------------------------------\n");

	t_ft_list *head2;
	t_ft_list *node3 = (t_ft_list *)malloc(sizeof(t_ft_list));
	t_ft_list *node4 = (t_ft_list *)malloc(sizeof(t_ft_list));
	head2 = node3;
	node3->val = 3;
	node3->next = node4;
	node4->val = 4;
	node4->next = NULL;

	printf("head2: ");
	iter = head2;
	while (iter)
	{
		printf("%d ", iter->val);
		iter = iter->next;
	}
	printf("\n");

	printf("\n<< SWAP A >>\n\n");
	swap_a(&head2);

	printf("head2: ");
	iter = head2;
	while (iter)
	{
		printf("%d ", iter->val);
		iter = iter->next;
	}
	printf("\n");

	printf("------------------------------------\n");
	
	printf("head1: ");
	iter = head1;
	while (iter)
	{
		printf("%d ", iter->val);
		iter = iter->next;
	}
	printf("\n");
	printf("head2: ");
	iter = head2;
	while (iter)
	{
		printf("%d ", iter->val);
		iter = iter->next;
	}
	printf("\n");

	printf("\n<< PUSH A >>\n\n");
	push_a(&head1, &head2);
	
	printf("head1: ");
	iter = head1;
	while (iter)
	{
		printf("%d ", iter->val);
		iter = iter->next;
	}
	printf("\n");
	printf("head2: ");
	iter = head2;
	while (iter)
	{
		printf("%d ", iter->val);
		iter = iter->next;
	}
	printf("\n");

	printf("------------------------------------\n");

	printf("head1: ");
	iter = head1;
	while (iter)
	{
		printf("%d ", iter->val);
		iter = iter->next;
	}
	printf("\n");

	printf("\n<< ROTATE A >>\n\n");
	rotate_a(&head1);

	printf("head1: ");
	iter = head1;
	while (iter)
	{
		printf("%d ", iter->val);
		iter = iter->next;
	}
	printf("\n");

	printf("\n<< ROTATE A >>\n\n");
	rotate_a(&head1);

	printf("head1: ");
	iter = head1;
	while (iter)
	{
		printf("%d ", iter->val);
		iter = iter->next;
	}
	printf("\n");

	printf("\n<< ROTATE A >>\n\n");
	rotate_a(&head1);

	printf("head1: ");
	iter = head1;
	while (iter)
	{
		printf("%d ", iter->val);
		iter = iter->next;
	}
	printf("\n");

	printf("------------------------------------\n");

	printf("head1: ");
	iter = head1;
	while (iter)
	{
		printf("%d ", iter->val);
		iter = iter->next;
	}
	printf("\n");

	printf("\n<< REVERSE ROTATE A >>\n\n");
	reverse_rotate_a(&head1);

	printf("head1: ");
	iter = head1;
	while (iter)
	{
		printf("%d ", iter->val);
		iter = iter->next;
	}
	printf("\n");

	printf("\n<< REVERSE ROTATE A >>\n\n");
	reverse_rotate_a(&head1);

	printf("head1: ");
	iter = head1;
	while (iter)
	{
		printf("%d ", iter->val);
		iter = iter->next;
	}
	printf("\n");

	printf("\n<< REVERSE ROTATE A >>\n\n");
	reverse_rotate_a(&head1);

	printf("head1: ");
	iter = head1;
	while (iter)
	{
		printf("%d ", iter->val);
		iter = iter->next;
	}
	printf("\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cir_dlst_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:08:50 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/27 18:26:51 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

int	ft_value_cmp(t_dlist *a, t_dlist *b)
{
	return (a->value < b->value);
}

void	ft_cir_dlstclear(t_dlist **my_dlst)
{
	t_dlist	*cur_node;
	t_dlist	*next_node;

	if (*my_dlst)
	{
		if (*my_dlst == (*my_dlst)->next)
			free (*my_dlst);
		else
		{
			cur_node = *my_dlst;
			while (1)
			{
				next_node = cur_node->next;
				free(cur_node);
				if (next_node == *my_dlst)
					break ;
				cur_node = next_node;
			}
		}
		*my_dlst = NULL;
	}
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

size_t	ft_cir_dlstsize(t_dlist *lst)
{
	t_dlist *cur_node;
	size_t	size;

	cur_node = lst;
	size = 0;
	while (cur_node)
	{
		size++;
		if (cur_node->next == lst)
			break ;
		cur_node = cur_node->next;
	}
	return (size);
}

void	ft_cir_dlstadd_back(t_dlist **lst, t_dlist *new)
{
	if (!*lst) // list가 비어있을때, '리스트의 헤더를 담당하는 노드'의 '주소값'을 넘겨줌, 노드가 가진 주소값이 아니라 노드 자체의 주소값임
	{
		*lst = new;
		new->prev = new;
		new->next = new;
	}
	else
	{
		new->prev = (*lst)->prev;
		new->next = *lst;
		(new->prev)->next = new;
		(new->next)->prev = new;
	}
}

void	ft_cir_dlstadd_front(t_dlist **lst, t_dlist *new)
{
	ft_cir_dlstadd_back(lst, new);
	if ((*lst)->next != *lst)
		*lst = (*lst)->prev;
		// 헤더만 옮겨준다
}

t_dlist *ft_dlstnew(int value)
{
	t_dlist *new;

	new = (t_dlist *)malloc(sizeof(t_dlist));
	if (!new)
		return (NULL);
	new->value = value;
	return (new);
}
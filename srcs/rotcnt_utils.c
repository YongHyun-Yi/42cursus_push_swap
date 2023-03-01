/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotcnt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:37:10 by yonghyle          #+#    #+#             */
/*   Updated: 2023/03/02 00:00:03 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

long long	get_rotcnt_totop(t_dlist *my_stack, t_dlist *target_node)
{
	long long	rot_cnt;
	t_dlist		*cur_node;

	rot_cnt = 0;
	cur_node = my_stack;
	while (1)
	{
		if (cur_node == target_node)
			break ;
		rot_cnt++;
		cur_node = cur_node->next;
	}
	if ((unsigned long long)rot_cnt > ft_cir_dlstsize(my_stack) - rot_cnt)
		rot_cnt -= ft_cir_dlstsize(my_stack);
	return (rot_cnt);
}

long long	get_rotcnt_topos(t_dlist *my_stack, t_dlist *target_node)
{
	long long	rot_cnt;
	t_dlist		*cur_node;

	if (my_stack == NULL)
		return (0);
	if (target_node->value < get_smallest_node(my_stack)->value)
		return (get_rotcnt_totop(my_stack, get_smallest_node(my_stack)));
	else if (target_node->value > get_largest_node(my_stack)->value)
		return (get_rotcnt_totop(my_stack, get_smallest_node(my_stack)));
	rot_cnt = 0;
	cur_node = my_stack;
	while (!(target_node->value < cur_node->value
			&& target_node->value > (cur_node->prev)->value))
	{
		if (cur_node->next == my_stack)
			break ;
		rot_cnt++;
		cur_node = cur_node->next;
	}
	if ((unsigned long long)rot_cnt > ft_cir_dlstsize(my_stack) - rot_cnt)
		rot_cnt -= ft_cir_dlstsize(my_stack);
	return (rot_cnt);
}

long long	get_double_rotcnt(t_dlist *dest, t_dlist *src, t_dlist *target_node)
{
	long long	dest_rotcnt;
	long long	src_rotcnt;

	dest_rotcnt = get_rotcnt_topos(dest, target_node);
	src_rotcnt = get_rotcnt_totop(src, target_node);
	if ((dest_rotcnt > 0) != (src_rotcnt > 0))
		return (0);
	if (my_abs(dest_rotcnt) > my_abs(src_rotcnt))
		return (src_rotcnt);
	return (dest_rotcnt);
}

size_t	get_total_rotcnt(t_dlist *dest, t_dlist *src, t_dlist *target_node)
{
	long long	dest_rotcnt;
	long long	src_rotcnt;
	long long	double_rotcnt;

	dest_rotcnt = get_rotcnt_topos(dest, target_node);
	src_rotcnt = get_rotcnt_totop(src, target_node);
	double_rotcnt = get_double_rotcnt(dest, src, target_node);
	if (double_rotcnt)
	{
		if (my_abs(dest_rotcnt) > my_abs(src_rotcnt))
			return (my_abs(dest_rotcnt));
		return (my_abs(src_rotcnt));
	}
	return (my_abs(dest_rotcnt) + my_abs(src_rotcnt));
}

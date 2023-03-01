/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:30:07 by yonghyle          #+#    #+#             */
/*   Updated: 2023/03/01 23:28:40 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_total_rotcnt_cmp(t_dlist *dest, t_dlist *src, t_dlist *a, t_dlist *b)
{
	return (get_total_rotcnt(dest, src, a) <= get_total_rotcnt(dest, src, b));
}

int	ft_value_cmp(t_dlist *a, t_dlist *b)
{
	return (a->value < b->value);
}

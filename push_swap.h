/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:48:24 by yonghyle          #+#    #+#             */
/*   Updated: 2023/01/27 12:24:05 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
// # include "libft.h"
// # include "ft_printf.h"

typedef struct s_ft_list
{
	int					val;
	struct s_ft_list	*next;
}	t_ft_list;

void	swap_a(t_ft_list **stack_a);
void	swap_b(void);
void	swap_a_swap_b(void);
void	push_a(t_ft_list **stack_a, t_ft_list **stack_b);
void	push_b(void);
void	rotate_a(t_ft_list **stack_a);
void	rotate_b(void);
void	rotate_a_rotate_b(void);
void	reverse_rotate_a(t_ft_list **stack_a);
void	reverse_rotate_b(void);
void	reverse_rotate_a_rotate_b(void);

#endif
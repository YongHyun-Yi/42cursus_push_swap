/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:48:24 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/16 14:27:23 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

# define SUCCESS 1
# define FAIL 0

typedef struct s_ft_list
{
	int					val;
	struct s_ft_list	*next;
}	t_ft_list;

typedef struct s_dlist
{
	int				value;
	struct s_dlist	*prev;
	struct s_dlist	*next;
}	t_dlist;

typedef struct s_ps_stat
{
	t_ft_list	*stack_a;
	t_ft_list	*stack_b;
}	t_ps_stat;

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
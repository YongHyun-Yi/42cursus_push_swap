/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:26:16 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/15 10:28:10 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strisint(char *str)
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
	if (!ft_strisnum(str + has_sign, ft_isdigit))
		return (0);
	if (ft_strlen(str + has_sign) > 10)
		return (0);
	else if (ft_strlen(str + has_sign) == 10)
	{
		if ((str + has_sign)[0] > '2')
			return (0);
	}
	if ((ft_atoi(str) >= 0) != is_postive)
		return (0);
	return (1);
}

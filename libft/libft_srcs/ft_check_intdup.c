/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_intdup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:50:30 by yonghyle          #+#    #+#             */
/*   Updated: 2023/02/15 11:01:18 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check_intdup(char *bit_array, unsigned int num)
{
	int	div;
	int	mod;

	div = num / 8;
	mod = num % 8;
	if (*(bit_array + div) & (1 << mod))
		return (0);
	*(bit_array + div) = (*(bit_array + div) | (1 << mod));
	return (1);
}

// calloc에서 꽤나 시간이 걸림...

///////////// 비트 마스킹 간단 실습 /////////////////
	
	// char *bit_masking = ft_calloc(1, sizeof(char)); // -> char : 1byte = 8bit ->> 8개의 요소에 대해서 중복체크 가능

	// int num = 4;
	
	// *bit_masking = *bit_masking | (1 << num);

	// if (*bit_masking & (1 << num))
	// 	printf("This bit array has %d\n", num);
	// else
	// 	printf("This bit array hasn't %d\n", num);

	/////////////////////////////////////////////
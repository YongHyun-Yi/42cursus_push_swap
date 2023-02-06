/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:13:09 by yonghyle          #+#    #+#             */
/*   Updated: 2022/11/21 15:06:02 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_splits(char const *s, char c)
{
	int	is_del;
	int	cnt;

	is_del = 1;
	cnt = 0;
	while (*s)
	{
		if (is_del && *s != c)
		{
			is_del = 0;
			cnt++;
		}
		else if (!is_del && *s == c)
			is_del = 1;
		s++;
	}
	return (cnt);
}

static char	*get_split_str(char const *s, char c, size_t *ori_index)
{
	int		serch_index;
	char	*split_str;

	serch_index = *ori_index;
	while (s[serch_index] != c && s[serch_index])
		serch_index++;
	split_str = ft_substr(s, *ori_index, serch_index - *ori_index);
	if (split_str)
		*ori_index += serch_index - *ori_index;
	return (split_str);
}

static void	free_all(char **splits, size_t split_index)
{
	while (split_index > 0)
		free(splits[--split_index]);
	free(splits);
}

char	**ft_split(char const *s, char c)
{
	char	**splits;
	size_t	split_index;
	size_t	current_char;

	splits = (char **)malloc(sizeof(char *) * ((count_splits(s, c) + 1)));
	if (!splits)
		return (0);
	splits[count_splits(s, c)] = 0;
	split_index = 0;
	current_char = 0;
	while (s[current_char])
	{
		while (s[current_char] == c && s[current_char])
			current_char++;
		if (s[current_char])
		{
			splits[split_index] = get_split_str(s, c, &current_char);
			if (!splits[split_index++])
			{
				free_all(splits, split_index);
				return (0);
			}
		}
	}
	return (splits);
}

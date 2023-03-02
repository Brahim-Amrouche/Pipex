/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 20:34:38 by bamrouch          #+#    #+#             */
/*   Updated: 2023/03/02 13:31:00 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#define SPLIT_SCOPE 2

static char	**ft_malloc_splits(char *s, t_boolean (*sep_checker)(char))
{
	size_t	count;
	size_t	i;
	char	**res;

	if (!s)
		return (NULL);
	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && sep_checker(s[i]))
			i++;
		if (s[i])
			count++;
		while (s[i] && !sep_checker(s[i]))
			i++;
	}
	res = ft_malloc((count + 1) * sizeof(char *), (t_mem_manage_params){NULL,
			SPLIT_SCOPE, NULL, 0});
	if (res)
		ft_bzero(res, sizeof(char *) * (count + 1));
	return (res);
}

static size_t	ft_make_splits(char **splits, char const *s,
		t_boolean (*sep_checker)(char))
{
	size_t	split_size;
	size_t	split_pos;

	split_size = 0;
	split_pos = -1;
	while (s[split_size] && !sep_checker(s[split_size]))
		split_size++;
	while (splits[++split_pos])
		;
	splits[split_pos] = protected_substr(s, 0, split_size);
	if (!splits[split_pos])
		return (0);
	return (split_size);
}

char	**ft_split_multi_sep(char *s, t_boolean (*sep_checker)(char))
{
	char	**res;
	size_t	temp;
	size_t	i;

	res = ft_malloc_splits(s, sep_checker);
	if (!res)
		return (NULL);
	i = 0;
	while (s[i])
	{
		while (s[i] && sep_checker(s[i]))
			i++;
		if (s[i])
		{
			temp = ft_make_splits(res, (s + i), sep_checker);
			if (!temp)
				return (NULL);
			i += temp;
		}
	}
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicat_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 21:08:41 by bamrouch          #+#    #+#             */
/*   Updated: 2023/03/01 19:52:37 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strdup_protected(char *s1)
{
	size_t	s_len;
	size_t	i;
	char	*res;

	if (!s1)
		return (NULL);
	s_len = ft_strlen(s1);
	res = ft_malloc((s_len + 1) * sizeof(char),
			(t_mem_manage_params){NULL, 2, NULL, 0});
	if (!res)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:33:51 by bamrouch          #+#    #+#             */
/*   Updated: 2023/03/01 19:52:51 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin_protected(char *s1, char *s2)
{
	size_t	total_len;
	size_t	s1_len;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1) + 1;
	total_len = s1_len + ft_strlen(s2);
	res = (char *)ft_malloc(total_len * sizeof(char),
			(t_mem_manage_params){NULL, 2, NULL, 0});
	if (!res)
		return (NULL);
	res[0] = 0;
	ft_strlcat(res, s1, s1_len);
	ft_strlcat(res, s2, total_len);
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 20:42:07 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/22 21:03:17 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_garbage_collector.h"

size_t	gnl_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (*(str + i))
		i++;
	return (i);
}

size_t	gnl_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;
	size_t	dst_len;

	src_len = gnl_strlen(src);
	if (!dst && !dstsize)
		return (src_len);
	dst_len = gnl_strlen(dst);
	i = 0;
	if (dstsize <= dst_len || dstsize == 0)
		return (src_len + dstsize);
	while (i < dstsize - dst_len - 1 && i < src_len)
	{
		dst[(dst_len + i)] = src[i];
		i++;
	}
	dst[(dst_len + i)] = '\0';
	return (src_len + dst_len);
}

void	gnl_strjoin(char **line, char *buffer)
{
	size_t	total_len;
	size_t	s1_len;
	char	*old_line;

	old_line = *line;
	s1_len = gnl_strlen(old_line);
	total_len = s1_len + gnl_strlen(buffer);
	*line = ft_malloc((total_len + 1) * sizeof(char),
			(t_mem_manage_params){NULL, GNL_SCOPE, NULL, 0});
	if (!(*line))
		return ;
	*line[0] = 0;
	gnl_strlcat(*line, old_line, s1_len + 1);
	ft_free_node(GNL_SCOPE, old_line);
	gnl_strlcat(*line, buffer, total_len + 1);
}

char	*gnl_substr(char *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	i;
	char	*res;

	if (!s)
		return (NULL);
	s_len = gnl_strlen(s);
	if (start >= s_len)
		len = 0;
	if (len >= s_len - start)
		len = s_len - start;
	res = ft_malloc((len + 1) * sizeof(char), (t_mem_manage_params){NULL,
			GNL_SCOPE, NULL, 0});
	if (!res)
		return (NULL);
	i = 0;
	while (i < len && start + i < s_len)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = 0;
	return (res);
}

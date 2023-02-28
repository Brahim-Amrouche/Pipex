/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:53:38 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/28 21:03:34 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_garbage_collector.h"

static long	find_new_line(char *str)
{
	ssize_t	i;

	if (!str)
		return (-1);
	i = 0;
	while (*(str + i) && *(str + i) != '\n')
		i++;
	if (*(str + i))
		return (i);
	return (-1);
}

static char	*gnl_line(char **line, ssize_t pos)
{
	size_t	rest_len;
	char	*res;
	char	*temp;

	if (pos == -1)
	{
		temp = *line;
		*line = NULL;
		return (temp);
	}
	res = gnl_substr(*line, 0, pos + 1);
	if (!res)
	{
		*line = NULL;
		return (NULL);
	}
	rest_len = gnl_strlen(*line);
	temp = *line;
	*line = gnl_substr(*line, pos + 1, rest_len);
	if (!(*line))
		return (*line);
	ft_free_node(GNL_SCOPE, temp);
	return (res);
}

static char	*gnl_helper(int fd, char **res)
{
	ssize_t	read_count;
	ssize_t	nl_pos;
	char	buffer[BUFFER_SIZE + 1];

	read_count = read(fd, buffer, BUFFER_SIZE);
	if (read_count == -1)
	{
		ft_free_node(GNL_SCOPE, *res);
		*res = NULL;
		return (*res);
	}
	while (read_count >= 0 || *res)
	{
		buffer[read_count] = 0;
		if (read_count)
			gnl_strjoin(res, buffer);
		nl_pos = find_new_line(*res);
		if (nl_pos >= 0)
			return (gnl_line(res, nl_pos));
		if (!read_count && nl_pos == -1)
			return (gnl_line(res, nl_pos));
		read_count = read(fd, buffer, BUFFER_SIZE);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*keeper[10241];
	char		*res;

	if (fd < 0 || fd > 10240 || BUFFER_SIZE <= 0)
		return (NULL);
	res = gnl_helper(fd, &(keeper[fd]));
	mem_move((t_mem_manage_params){NULL, GNL_SCOPE, res, 1});
	return (res);
}

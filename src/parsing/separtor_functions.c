/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separtor_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 20:41:50 by bamrouch          #+#    #+#             */
/*   Updated: 2023/03/03 23:16:44 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_boolean	str_is_a_path(char *str)
{
	size_t	last_back_slash;
	char	*duplicat_path;

	if (!str)
		return (FALSE);
	last_back_slash = 0;
	if (str[last_back_slash] == '/')
		return (TRUE);
	while (str[last_back_slash] && str[last_back_slash] != '/')
		last_back_slash++;
	if (str[last_back_slash] == '/')
	{
		duplicat_path = protected_substr(str, 0, last_back_slash);
		if (!access(duplicat_path, F_OK))
		{
			ft_free_node(2, duplicat_path);
			return (TRUE);
		}
		ft_free_node(2, duplicat_path);
	}
	return (FALSE);
}

t_boolean	path_sep(char c)
{
	if (c == ':')
		return (TRUE);
	return (FALSE);
}

t_boolean	cmd_sep(char c)
{
	if (c == ' ' || c == '\t')
		return (TRUE);
	return (FALSE);
}

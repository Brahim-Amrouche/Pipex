/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:50:32 by bamrouch          #+#    #+#             */
/*   Updated: 2023/03/03 23:15:21 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_boolean	protected_putchar_fd(int fd, char c)
{
	if (write(fd, &c, 1) == -1)
		return (FALSE);
	return (TRUE);
}

t_boolean	protected_putstr_fd(int fd, char *str)
{
	size_t	i;

	if (!str)
		return (TRUE);
	i = 0;
	while (str[i])
	{
		if (!protected_putchar_fd(fd, str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_boolean	protected_putendl_fd(char *s, int fd)
{
	if (!protected_putstr_fd(fd, s)
		|| !protected_putchar_fd(fd, '\n'))
		return (FALSE);
	return (TRUE);
}

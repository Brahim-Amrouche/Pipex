/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:50:32 by bamrouch          #+#    #+#             */
/*   Updated: 2023/03/01 19:53:11 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	protected_putchar_fd(int fd, char c)
{
	if (write(fd, &c, 1) == -1)
		exit_pipex(EIO, "couldn't write to fd", TRUE);
}

void	protected_putstr_fd(int fd, char *str)
{
	while (*str)
	{
		protected_putchar_fd(fd, *str);
		str++;
	}
}

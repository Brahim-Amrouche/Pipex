/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:57:42 by bamrouch          #+#    #+#             */
/*   Updated: 2023/03/05 19:44:58 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fd(int fd)
{
	if (fd >= 0 && close(fd) == -1)
		exit_pipex(EAGAIN, "couldn't close a file descriptor", TRUE);
}

void	close_pipe(int *fd)
{
	close_fd(fd[0]);
	close_fd(fd[1]);
}

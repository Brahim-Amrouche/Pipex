/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:57:42 by bamrouch          #+#    #+#             */
/*   Updated: 2023/03/04 14:42:31 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fd(int fd)
{
	if (fd >= 0 && close(fd) == -1)
		exit_pipex(EAGAIN, "couldn't close a file descriptor", TRUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:17:24 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/21 15:51:17 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void   pipex_main_process()
{
    int fd[2];
    pid_t	childprocess;

    if (pipe(fd))
        exit_pipex(EPIPE, "couldn't pipe", TRUE);
    childprocess = fork();
	if (childprocess == -1)
        exit_pipex(EAGAIN, "couldn't fork", TRUE);
    if (!childprocess)
    {
        close(fd[1]);
        ft_printf("%s",get_next_line(fd[0]));
    }
    else
    {
        close(fd[0]);
        ft_putstr_fd("hello bro \n",fd[1]);
    }
}

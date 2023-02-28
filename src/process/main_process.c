/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:17:24 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/25 20:0 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <signal.h>

static void close_pipe(int *fd)
{
	close(fd[0]);
    close(fd[1]);
}

static void	child_process(t_pipex *pipex, size_t cmd)
{
	close(pipex->com_pipe[1]);
    close(pipex->pass_pipe[0]);
    if (cmd == 0)
	{
        dup2(pipex->in_file, STDIN_FILENO);
		close(pipex->in_file);
	}
	else
        dup2(pipex->com_pipe[0], STDIN_FILENO);
    close(pipex->com_pipe[0]);
    if (cmd == pipex->cmds_count - 1)
	{
		dup2(pipex->out_file, STDOUT_FILENO);
		close(pipex->out_file);
	}
	else
        dup2(pipex->pass_pipe[1], STDOUT_FILENO);
    close(pipex->pass_pipe[1]);
    if(execve((pipex->cmds)[cmd][0], (pipex->cmds)[cmd], pipex->envp) == -1)
        exit_pipex(EAGAIN, "couldn't execve childprocess", TRUE);
}


static void    execute_cmd(t_pipex *pipex, size_t cmd)
{
    pid_t childprocess;

    childprocess = fork();    
    if (childprocess == -1)
        exit_pipex(EAGAIN, "couldn't fork child process", TRUE);
    if (childprocess == 0)
		child_process(pipex, cmd);
    else
    {
        close_pipe(pipex->com_pipe);
        if(cmd == pipex->cmds_count - 1)
            close_pipe(pipex->pass_pipe);
    }
    waitpid(childprocess, NULL, 0);
}


void    main_process(t_pipex *pipex)
{
    size_t	i;
    int		fd_1[2];
	int		fd_2[2]; 

    if (pipe(fd_1) || pipe(fd_2))
        exit_pipex(EPIPE, "couldn't pipe", TRUE);
	pipex->com_pipe = fd_1;
	pipex->pass_pipe = fd_2;
    i = 0;
    while (i < pipex->cmds_count)
    {
        execute_cmd(pipex, i);
		if (i < pipex->cmds_count - 1)
		{
			pipex->com_pipe = pipex->pass_pipe;
        	if (pipe(fd_1))
            	exit_pipex(EPIPE, "couldn't pipe", TRUE);
			pipex->pass_pipe = fd_1;
		}
		i++;
    }
}

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

static void	close_pipe(int *fd)
{
	close_fd(fd[0]);
	close_fd(fd[1]);
}

static void	child_process(t_pipex *pipex, size_t cmd)
{
	close_fd(pipex->com_pipe[1]);
	close_fd(pipex->pass_pipe[0]);
	if (cmd == 0)
	{
		dup2(pipex->in_file, STDIN_FILENO);
		close_fd(pipex->in_file);
	}
	else
		dup2(pipex->com_pipe[0], STDIN_FILENO);
	close_fd(pipex->com_pipe[0]);
	if (cmd == pipex->cmds_count - 1)
	{
		dup2(pipex->out_file, STDOUT_FILENO);
		close_fd(pipex->out_file);
	}
	else
		dup2(pipex->pass_pipe[1], STDOUT_FILENO);
	close_fd(pipex->pass_pipe[1]);
	if (execve((pipex->cmds)[cmd][0], (pipex->cmds)[cmd], pipex->envp) == -1)
		exit_pipex(EAGAIN, "couldn't execve childprocess", TRUE);
}

static void	execute_cmd(t_pipex *pipex, size_t cmd)
{
	pid_t	childprocess;

	childprocess = fork();
	if (childprocess == -1)
		exit_pipex(EAGAIN, "couldn't fork child process", TRUE);
	if (childprocess == 0)
		child_process(pipex, cmd);
	else
	{
		close_pipe(pipex->com_pipe);
		if (cmd == pipex->cmds_count)
			close_pipe(pipex->pass_pipe);
	}
}

void	main_process(t_pipex *pipex)
{
	size_t	i;

	if (pipe(pipex->com_pipe) || pipe(pipex->pass_pipe))
		exit_pipex(EPIPE, "couldn't pipe", TRUE);
	i = 0;
	while (i < pipex->cmds_count)
	{
		execute_cmd(pipex, i);
		if (i < pipex->cmds_count - 1)
		{
			pipex->com_pipe[0] = pipex->pass_pipe[0];
			pipex->com_pipe[1] = pipex->pass_pipe[1];
			if (pipe(pipex->pass_pipe))
				exit_pipex(EPIPE, "couldn't pipe", TRUE);
		}
		i++;
	}
	while (wait(NULL) != -1)
	{

	};
	waitpid(0, NULL, 0);
	close_fd(pipex->in_file);
	close_fd(pipex->out_file);
}

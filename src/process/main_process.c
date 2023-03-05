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

static void	open_file(t_pipex *pipex, t_boolean for_read)
{
	if (for_read)
	{
		if (pipex->with_heredoc)
			pipex->in_file_fd = open(HEREDOC_PATH, O_RDONLY);
		else
			pipex->in_file_fd = open(pipex->in_file, O_RDONLY);
		dup2(pipex->in_file_fd, STDIN_FILENO);
		close_fd(pipex->in_file_fd);
		if (pipex->in_file_fd < 0)
			pipex->read_error = TRUE;
		return ;
	}
	if (pipex->with_heredoc)
		pipex->out_file_fd = open(pipex->out_file,
				O_APPEND | O_CREAT | O_WRONLY | O_SYMLINK, 0666);
	else
		pipex->out_file_fd = open(pipex->out_file,
				O_TRUNC | O_CREAT | O_WRONLY | O_SYMLINK, 0666);
	dup2(pipex->out_file_fd, STDOUT_FILENO);
	close_fd(pipex->out_file_fd);
	if (pipex->out_file_fd < 0)
		pipex->write_error = TRUE;
}

static void	child_process(t_pipex *pipex, size_t cmd)
{
	close_fd(pipex->com_pipe[1]);
	close_fd(pipex->pass_pipe[0]);
	if (cmd == 0)
		open_file(pipex, TRUE);
	else
		dup2(pipex->com_pipe[0], STDIN_FILENO);
	close_fd(pipex->com_pipe[0]);
	if (cmd == pipex->cmds_count - 1)
		open_file(pipex, FALSE);
	else
		dup2(pipex->pass_pipe[1], STDOUT_FILENO);
	close_fd(pipex->pass_pipe[1]);
	if (pipex->read_error)
		protected_putendl_fd("no such read file", STDERR_FILENO);
	if (pipex->write_error)
		protected_putendl_fd("cant write to out file", STDERR_FILENO);
	if (pipex->read_error || pipex->write_error)
		exit_pipex(-1, NULL, TRUE);
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
		if (cmd == pipex->cmds_count - 1)
		{
			pipex->last_process = childprocess;
			close_pipe(pipex->pass_pipe);
		}
	}
}

static void	wait_child_processes(t_pipex *pipex)
{
	pid_t	process_id;

	process_id = 0;
	while (process_id != -1)
	{
		process_id = wait(&pipex->exit_status);
		if (process_id == pipex->last_process && pipex->exit_status)
			exit_pipex(-1, NULL, TRUE);
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
	wait_child_processes(pipex);
}

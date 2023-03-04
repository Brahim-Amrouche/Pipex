/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 21:05:33 by bamrouch          #+#    #+#             */
/*   Updated: 2023/03/04 18:18:30 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	limiter_initializer(t_pipex *pipex, char *argv[])
{
	pipex->hd_limiter = ft_strjoin_protected(argv[2], "\n");
	if (!pipex->hd_limiter)
		exit_pipex(ENOMEM, "couldn't malloc limiter", TRUE);
	pipex->hd_limiter_len = ft_strlen(pipex->hd_limiter);
}

static void	read_here_doc(t_pipex *pipex, char *argv[])
{
	char	*res;

	pipex->in_file = open(HEREDOC_PATH, O_TRUNC | O_CREAT | O_WRONLY, 0666);
	if (pipex->in_file == -1)
		exit_pipex(EAGAIN, "couldn't create heredoc", TRUE);
	protected_putstr_fd(STDOUT_FILENO, "here_doc>");
	res = get_next_line(STDIN_FILENO);
	limiter_initializer(pipex, argv);
	while (protected_strncmp(res, pipex->hd_limiter, pipex->hd_limiter_len))
	{
		protected_putstr_fd(pipex->in_file, res);
		protected_putstr_fd(STDOUT_FILENO, "here_doc>");
		ft_free_node(1, res);
		res = get_next_line(STDIN_FILENO);
	}
	ft_free_node(2, pipex->hd_limiter);
	close_fd(pipex->in_file);
	pipex->in_file = open(HEREDOC_PATH, O_RDONLY);
	if (pipex->in_file == -1)
		exit_pipex(EAGAIN, "couldn't open heredoc for read", TRUE);
	pipex->with_heredoc = TRUE;
}

static void	read_file(t_pipex *pipex, char *argv[])
{
	pipex->in_file = open(argv[1], O_RDONLY);
	if (pipex->in_file == -1)
		exit_pipex(EAGAIN, "couldn't open the read file", TRUE);
}

void	pipex_bonus_parser(t_pipex *pipex, int argc, char *argv[], char *envp[])
{
	if (argc < 4)
		exit_pipex(EINVAL, "not enough arguments", TRUE);
	if (!protected_strncmp(argv[1], "here_doc", 9) && argc >= 5)
	{
		read_here_doc(pipex, argv);
		argv++;
	}
	else if (access(argv[1], R_OK) == 0)
		read_file(pipex, argv);
	else
		protected_putendl_fd("no such read file", STDERR_FILENO);
	pipex->envp = envp;
	pipex->cmds = split_command_params(pipex, argc, argv);
	while ((pipex->cmds)[pipex->cmds_count])
		pipex->cmds_count++;
	if (pipex->with_heredoc)
		pipex->out_file = open(argv[argc - 2],
				O_APPEND | O_CREAT | O_WRONLY | O_SYMLINK, 0666);
	else
		pipex->out_file = open(argv[argc - 1],
				O_TRUNC | O_CREAT | O_WRONLY | O_SYMLINK, 0666);
	if (pipex->out_file == -1)
		protected_putendl_fd("couldn't create output file", STDERR_FILENO);
}

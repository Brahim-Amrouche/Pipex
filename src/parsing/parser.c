/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:19:28 by bamrouch          #+#    #+#             */
/*   Updated: 2023/03/04 16:16:53 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_parser(t_pipex *pipex, int argc, char *argv[], char *envp[])
{
	if (argc < 5 || argc > 5)
		exit_pipex(EINVAL, "invalid arguments count ==> you need 4 arguments",
			TRUE);
	pipex->in_file = open(argv[1], O_RDONLY);
	if (pipex->in_file == -1)
		protected_putendl_fd("no such read file", STDERR_FILENO);
	pipex->envp = envp;
	pipex->cmds = split_command_params(pipex, argc, argv);
	while ((pipex->cmds)[pipex->cmds_count])
		pipex->cmds_count++;
	pipex->out_file = open(argv[4], O_TRUNC | O_CREAT | O_WRONLY | O_SYMLINK,
			0666);
	if (pipex->out_file == -1)
		protected_putendl_fd("couldn't create output file", STDERR_FILENO);
}

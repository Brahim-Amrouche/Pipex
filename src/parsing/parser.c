/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:19:28 by bamrouch          #+#    #+#             */
/*   Updated: 2023/03/05 18:00:14 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_parser(t_pipex *pipex, int argc, char *argv[], char *envp[])
{
	if (argc < 5 || argc > 5)
		exit_pipex(EINVAL, "invalid arguments count ==> you need 4 arguments",
			TRUE);
	pipex->in_file = argv[1];
	pipex->envp = envp;
	pipex->cmds = split_command_params(pipex, argc, argv);
	while ((pipex->cmds)[pipex->cmds_count])
		pipex->cmds_count++;
	pipex->out_file = argv[4];
}

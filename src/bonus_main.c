/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 19:37:00 by bamrouch          #+#    #+#             */
/*   Updated: 2023/03/02 14:01:33 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	ft_bzero(&pipex, sizeof(t_pipex));
	pipex_bonus_parser(&pipex, argc, argv, envp);
	main_process(&pipex);
	exit_pipex(0, NULL, FALSE);
}

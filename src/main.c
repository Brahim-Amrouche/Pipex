/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:08:02 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/28 22:43:38 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char *argv[], char *envp[])
{
    t_pipex pipex;

    ft_bzero(&pipex, sizeof(t_pipex));
    pipex_parser(&pipex, argc, argv, envp);
    main_process(&pipex);
    exit_pipex(0, NULL, FALSE);
}
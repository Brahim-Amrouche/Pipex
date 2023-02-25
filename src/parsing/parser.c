/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:19:28 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/25 20:50:50 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_boolean path_sep(char c)
{
    if (c == ':')
        return TRUE;
    return FALSE;
}

static  char **parse_path(char *envp[])
{
    while (*envp)
    {
        if (ft_strncmp(*envp, "PATH", 4) == 0)
            break;
        envp++;
    }
    return (ft_split_multi_sep(*envp, path_sep));
}

char ***pipex_parser(int argc, char *argv[], char *envp[])
{
    char **paths;

    if(argc < 5 || argc > 5)
        exit_pipex(EINVAL, "invalid arguments=> numbers you need 4 arguments", TRUE);
    else if(access(argv[1], R_OK) == -1)
        exit_pipex(EINVAL, "invalid arguments=> couldn't open read file", TRUE);
    paths = parse_path(envp);
    return (split_command_params(argc, argv, paths));
}
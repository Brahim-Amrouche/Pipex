/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:42:49 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/25 18:24:56 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


static  t_boolean cmd_sep(char c)
{
    if (c == ' ' || c == '\t')
        return TRUE;
    return FALSE;
}

char ***split_command_params(int argc, char *argv[])
{
    ssize_t i;
    char    ***pipe_args;

    i = -1;
    argv++;
    pipe_args = ft_malloc((argc - 2) * sizeof(char **), 
        (t_mem_manage_params){NULL, 1, NULL, 0});
    while((++i) < argc - 3  && ++argv)
    {
        *(pipe_args + i) = ft_split_multi_sep(*argv, cmd_sep);
        if (!(*pipe_args + i))
            exit_pipex(ENOMEM, "couldn't malloc arguments split", TRUE);
    }
    *(pipe_args + i) = NULL;
    return pipe_args;
}


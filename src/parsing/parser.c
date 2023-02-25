/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:19:28 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/25 18:25:43 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"



char ***pipex_parser(int argc, char *argv[])
{
    if(argc < 5 || argc > 5)
        exit_pipex(EINVAL, "invalid arguments=> numbers you need 4 arguments", TRUE);
    else if(access(argv[1], R_OK) == -1)
        exit_pipex(EINVAL, "invalid arguments=> couldn't open read file", TRUE);
    return (split_command_params(argc, argv));
}
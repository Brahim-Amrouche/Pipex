/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:19:28 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/21 12:08:33 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void pipex_parser(int argc, char *argv[])
{
    if(argc < 5 || argc > 5 || access(argv[1], R_OK) || access(argv[5], W_OK))
        exit_pipex(EINVAL, "invalid arguments", TRUE);
}
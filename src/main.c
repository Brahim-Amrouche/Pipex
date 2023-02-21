/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:08:02 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/21 15:09:49 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char *argv[])
{
    pipex_parser(argc, argv);
    pipex_main_process();
    exit_pipex(0, NULL, FALSE);
}
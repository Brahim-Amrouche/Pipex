/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:30:05 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/21 15:09:33 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PIPEX_H
#define PIPEX_H
#include "ft_garbage_collector.h"
#include "errno.h"

// Parsing
//parser.c
void pipex_parser(int argc, char *argv[]);

//process
// main_process.c
void   pipex_main_process();

//exit_pipex.c
void    exit_pipex(int err_n, char *message, t_boolean is_error);


#endif

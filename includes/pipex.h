/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:30:05 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/26 16:56:19 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PIPEX_H
#define PIPEX_H
#include "ft_garbage_collector.h"
#include "errno.h"

// Parsing
// parser_helper.c
char    ***split_command_params(int argc, char *argv[], char *envp[]);
//parser.c
char    ***pipex_parser(int argc, char *argv[], char *envp[]);

//process
//child_process.c
void	child_process(int fd[2]);
// main_process.c
void    main_process(char ***argv, char *envp[]);

//utils
//join_util.c
char    *ft_strjoin_protected(char *s1, char *s2);
// split_util.c
char    **ft_split_multi_sep(char *s, t_boolean (*sep_checker)(char));

//exit_pipex.c
void	exit_pipex(int err_n, char *message, t_boolean is_error);


#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:30:05 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/28 22:37:04 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PIPEX_H
#define PIPEX_H
#include "ft_garbage_collector.h"
#include "errno.h"

#define HEREDOC_PATH "/tmp/heredoc.tmp"

typedef struct s_pipex
{
    int     *com_pipe;
    int     *pass_pipe;
    size_t  cmds_count;
    char    ***cmds;
    char    **envp;
    int     in_file;
    int     out_file;
    /* data */
} t_pipex;

// Parsing
// separator_functions
t_boolean	path_sep(char c);
t_boolean   cmd_sep(char c);


// parser_helper.c
char    ***split_command_params(int argc, char *argv[], char *envp[]);
//parser.c
void    pipex_parser(t_pipex *pipex, int argc, char *argv[], char *envp[]);

//process
// main_process.c
void    main_process(t_pipex *pipex);

//utils
//duplicat_util.c
char	*ft_strdup_protected(char *s1);
//join_util.c
char    *ft_strjoin_protected(char *s1, char *s2);
// split_util.c
char    **ft_split_multi_sep(char *s, t_boolean (*sep_checker)(char));

//exit_pipex.c
void	exit_pipex(int err_n, char *message, t_boolean is_error);


#endif

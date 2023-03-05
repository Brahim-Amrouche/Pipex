/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:30:05 by bamrouch          #+#    #+#             */
/*   Updated: 2023/03/05 18:28:37 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "errno.h"
# include "ft_garbage_collector.h"

# define HEREDOC_PATH "/tmp/heredoc.tmp"

typedef struct s_pipex
{
	int			com_pipe[2];
	int			pass_pipe[2];
	size_t		cmds_count;
	char		***cmds;
	char		**envp;
	t_boolean	with_heredoc;
	char		*hd_limiter;
	size_t		hd_limiter_len;
	char		*in_file;
	char		*out_file;
	int			in_file_fd;
	t_boolean	read_error;
	int			out_file_fd;
	t_boolean	write_error;
	pid_t		last_process;
	int			exit_status;
}				t_pipex;

// Parsing
// separator_functions
t_boolean		path_sep(char c);
t_boolean		cmd_sep(char c);
t_boolean		str_is_a_path(char *str);
// parser_helper.c
char			***split_command_params(t_pipex *pipex, int argc, char *argv[]);
//parser.c
void			pipex_parser(t_pipex *pipex, int argc, char *argv[],
					char *envp[]);
//bonus_parser.c
void			pipex_bonus_parser(t_pipex *pipex, int argc, char *argv[],
					char *envp[]);

//process
// main_process.c
void			main_process(t_pipex *pipex);

//utils
//duplicat_util.c
char			*ft_strdup_protected(char *s1);
//join_util.c
char			*ft_strjoin_protected(char *s1, char *s2);
// split_util.c
char			**ft_split_multi_sep(char *s, t_boolean (*sep_checker)(char));
// strncmp.c
int				protected_strncmp(char *s1, char *s2, size_t n);
// putstr.c
t_boolean		protected_putstr_fd(int fd, char *str);
t_boolean		protected_putendl_fd(char *s, int fd);
// close_fd.c
void			close_fd(int fd);
void			close_pipe(int *fd);
// substr.c
char			*protected_substr(char const *s, unsigned int start,
					size_t len);

//exit_pipex.c
void			exit_pipex(int err_n, char *message, t_boolean is_error);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:42:49 by bamrouch          #+#    #+#             */
/*   Updated: 2023/03/03 22:55:08 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	cmd_is_exect(char **cmd, char **paths)
{
	char		*joined_path;
	t_boolean	is_a_path;

	if (!access(*cmd, X_OK))
		return ;
	is_a_path = str_is_a_path(*cmd);
	while (!is_a_path && *paths)
	{
		joined_path = ft_strjoin_protected(*paths, *cmd);
		if (!joined_path)
			exit_pipex(ENOMEM, "could't find binary paths", TRUE);
		if (!access(joined_path, X_OK))
		{
			ft_free_node(2, *cmd);
			*cmd = joined_path;
			return ;
		}
		ft_free_node(2, joined_path);
		paths++;
	}
}

static void	add_ending_slash(char *paths[])
{
	size_t	path_len;
	char	*temp;

	while (*paths)
	{
		path_len = ft_strlen(*paths);
		if (*((*paths) + path_len - 1) != '/')
		{
			temp = *paths;
			*paths = ft_strjoin_protected(*paths, "/");
			if (!*paths)
				exit_pipex(ENOMEM, "couldn't add slash's to path", TRUE);
			ft_free_node(2, temp);
		}
		paths++;
	}
}

static char	**parse_path(char *envp[])
{
	char	*res;
	char	**paths;

	res = NULL;
	while (envp && *envp)
	{
		if (ft_strncmp(*envp, "PATH", 4) == 0)
		{
			res = (*envp + 5);
			break ;
		}
		envp++;
	}
	if (!res)
		paths = ft_split_multi_sep("", path_sep);
	else
		paths = ft_split_multi_sep(res, path_sep);
	if (!paths)
		exit_pipex(ENOMEM, "couldn't malloc path routes", TRUE);
	add_ending_slash(paths);
	return (paths);
}

static void	fix_memory(char **paths)
{
	size_t	i;

	i = 0;
	while (*(paths + i))
	{
		ft_free_node(2, *(paths + i));
		i++;
	}
	ft_free_node(2, paths);
	mem_scope_merge(2, 1);
}

char	***split_command_params(t_pipex *pipex, int argc, char *argv[])
{
	ssize_t	i;
	char	***pipe_args;
	char	**paths;

	i = -1;
	argv++;
	pipe_args = ft_malloc((argc - (2 + pipex->with_heredoc)) * sizeof(char **),
			(t_mem_manage_params){NULL, 1, NULL, 0});
	if (!pipe_args)
		exit_pipex(ENOMEM, "couldn't split args", TRUE);
	paths = parse_path(pipex->envp);
	while ((++i) < argc - (3 + pipex->with_heredoc) && ++argv)
	{
		*(pipe_args + i) = ft_split_multi_sep(*argv, cmd_sep);
		if (!(*pipe_args + i))
			exit_pipex(ENOMEM, "couldn't malloc arguments split", TRUE);
		cmd_is_exect(*(pipe_args + i), paths);
	}
	*(pipe_args + i) = NULL;
	fix_memory(paths);
	return (pipe_args);
}

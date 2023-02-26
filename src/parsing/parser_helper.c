/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:42:49 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/26 21:10:10 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_boolean	cmd_is_exect(char **cmd, char **paths)
{
	char *joined_path;

	if (!access(*cmd, X_OK))
		return TRUE;
	while(*paths)
	{
		joined_path = ft_strjoin_protected(*paths, *cmd);
		if (!joined_path)
			exit_pipex(ENOMEM, "could't fix binary paths", TRUE);
		if (!access(joined_path, X_OK))
		{
			*cmd = joined_path;
			return TRUE;
		}
		ft_free_node(2, joined_path);
		paths++;
	}

	return FALSE;
} 

static t_boolean	path_sep(char c)
{
	if (c == ':')
		return TRUE;
	return FALSE;
}

static  char    **parse_path(char *envp[])
{
	char	*res;
	char	**paths;
	size_t	i;
	char	*temp;
	
	if(!envp)
		return NULL;
	res = NULL;
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH", 4) == 0)
		{
			res = (*envp + 5);
			break;
		}
		envp++;
	}
	if (!res)
		return (ft_split_multi_sep("", path_sep));
	paths = ft_split_multi_sep(res, path_sep);
	if (!paths)
		exit_pipex(ENOMEM, "couldn't malloc path routes", TRUE);
	i = 0;
	// remake the array with slashes at the end **is fucked;
	while (*(paths + i))
	{
		temp = *(paths + i);
		*(paths + i) = ft_strjoin_protected(*(paths + i), "/");
		if (!*(paths + i))
			exit_pipex(ENOMEM, "couldn't malloc fixed paths", TRUE);
		ft_free_node(1, temp);
		i++;
	}
	return (paths);
}

static  t_boolean cmd_sep(char c)
{
	if (c == ' ' || c == '\t')
		return TRUE;
	return FALSE;
}

char ***split_command_params(int argc, char *argv[], char *envp[])
{
	ssize_t i;
	char    ***pipe_args;
	char    **paths;

	i = -1;
	argv++;
	pipe_args = ft_malloc((argc - 2) * sizeof(char **), 
		(t_mem_manage_params){NULL, 1, NULL, 0});
	if (!pipe_args)
		exit_pipex(ENOMEM, "couldn't split args", TRUE);
	paths = parse_path(envp);
	while((++i) < argc - 3  && ++argv)
	{
		*(pipe_args + i) = ft_split_multi_sep(*argv, cmd_sep);
		if (!(*pipe_args + i))
			exit_pipex(ENOMEM, "couldn't malloc arguments split", TRUE);
		if (cmd_is_exect(*(pipe_args + i), paths))
			continue;
		else
			exit_pipex(EINVAL, "invalid commands", TRUE);
	}
	*(pipe_args + i) = NULL;
	return pipe_args;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 21:05:33 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/28 22:50:32 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void    read_here_doc(t_pipex *pipex, char *argv[])
{
    char	*res;
    size_t	limiter_len; 

    if (access(HEREDOC_PATH, F_OK) == 0)
        if (unlink(argv[4]) == -1)
            exit_pipex(EAGAIN, "couldn't unlink heredoc file", TRUE);
    pipex->in_file = open(HEREDOC_PATH, O_CREAT | O_WRONLY, 0666);
	if (pipex->in_file == -1)
		exit_pipex(EAGAIN, "couldn't create heredoc", TRUE);
    res = get_next_line(STDIN_FILENO);
	limiter_len = ft_strlen(argv[2]);
	// find a way for empty "" LIMITER
    while ((!limiter_len && res) || (limiter_len && ft_strncmp(res, argv[2], limiter_len)))
    {
        ft_putstr_fd(res, pipex->in_file);
        res = get_next_line(STDIN_FILENO);
    }
    close(pipex->in_file);
	pipex->in_file = open(HEREDOC_PATH, O_RDONLY);
	if (pipex->in_file == -1)
		exit_pipex(EAGAIN, "couldn't create heredoc", TRUE);
}

void	read_file(t_pipex *pipex, char *argv[])
{
	pipex->in_file = open(argv[1], O_RDONLY);
    if (pipex->in_file == -1)
        exit_pipex(EAGAIN, "couldn't open the read file", TRUE);
}

void    pipex_bonus_parser(t_pipex *pipex, int argc, char *argv[], char *envp[])
{
    if(argc < 4)
        exit_pipex(EINVAL, "not enough arguments", TRUE);
    if (!ft_strncmp(argv[1], "here_doc", 8) && argc >= 5)
    {
        read_here_doc(pipex, argv);
        argv++;
    }
    else if (access(argv[1], R_OK) == 0)
        read_file(pipex, argv);
    else
        exit_pipex(EINVAL, "invalid argument => couldn't open read file", TRUE);
	pipex->envp = envp;
        
}
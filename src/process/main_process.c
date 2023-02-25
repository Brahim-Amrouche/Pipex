/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:17:24 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/25 20:0 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <signal.h>


void    pipe_process(int fd[2], char ***argv,char *envp[])
{
    pid_t   childprocess;
    pid_t   grandchildprocess;
    childprocess = fork();
	if (childprocess == -1)
        exit_pipex(EAGAIN, "couldn't fork child", TRUE);
    if (childprocess == 0)
    {
        grandchildprocess = fork();
        if (grandchildprocess == -1)
            exit_pipex(EAGAIN, "couldn't fork grandchild", TRUE);
        if (grandchildprocess == 0)
        {
            close(fd[0]);
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
            if(execve(argv[0][0], &(argv[0][1]), envp) == -1)
                exit_pipex(EAGAIN, "couldn't execve grandchild", TRUE);
        }
        else {
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            if(execve("ls", &(argv[1][1]), envp) == -1)
                exit_pipex(EAGAIN, "couldn't execve child", TRUE);
        }
    }
    else
    {
        close(fd[1]);
        close(fd[0]);
        wait(NULL);
    }
}


void    main_process(char ***argv, char *envp[])
{
    int fd[2];
    pid_t	childprocess;

    if (pipe(fd))
        exit_pipex(EPIPE, "couldn't pipe", TRUE);
    pipe_process(fd, argv, envp);
}

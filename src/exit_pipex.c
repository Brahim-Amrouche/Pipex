/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:36:50 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/25 16:28:05 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    exit_pipex(int err_n, char *message, t_boolean is_error)
{
    ft_free(0, TRUE);
    if (is_error)
    {
        ft_putstr_fd(strerror(err_n), STDERR_FILENO);
        ft_putstr_fd(":\t", STDERR_FILENO);
        ft_putendl_fd(message, STDERR_FILENO);
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
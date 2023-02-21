/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:36:50 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/21 11:45:06 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    exit_pipex(int err_n, char *message, t_boolean is_error)
{
    if (is_error)
    {
        perror(strerror(err_n));
        ft_putstr_fd(":\t", 2);
        ft_putendl_fd(message, 2);
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
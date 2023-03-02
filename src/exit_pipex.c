/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:36:50 by bamrouch          #+#    #+#             */
/*   Updated: 2023/03/02 15:08:04 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_pipex(int err_n, char *message, t_boolean is_error)
{
	ft_free(0, TRUE);
	if (is_error)
	{
		if (err_n >= 0)
			ft_putstr_fd(strerror(err_n), STDERR_FILENO);
		if (message)
		{
			ft_putstr_fd(":\t", STDERR_FILENO);
			ft_putendl_fd(message, STDERR_FILENO);
		}
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:36:50 by bamrouch          #+#    #+#             */
/*   Updated: 2023/03/03 23:17:20 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_pipex(int err_n, char *message, t_boolean is_error)
{
	ft_free(0, TRUE);
	if (is_error)
	{
		if (err_n >= 0)
			protected_putstr_fd(STDERR_FILENO, strerror(err_n));
		if (message)
		{
			protected_putstr_fd(STDERR_FILENO, ":\t");
			protected_putstr_fd(STDERR_FILENO, message);
			protected_putstr_fd(STDERR_FILENO, "\n");
		}
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

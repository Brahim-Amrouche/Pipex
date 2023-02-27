/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separtor_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 20:41:50 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/27 20:44:08 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_boolean	path_sep(char c)
{
	if (c == ':')
		return TRUE;
	return FALSE;
}

t_boolean cmd_sep(char c)
{
	if (c == ' ' || c == '\t')
		return TRUE;
	return FALSE;
}
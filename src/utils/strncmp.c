/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strncmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:33:53 by bamrouch          #+#    #+#             */
/*   Updated: 2023/03/01 19:39:15 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	protected_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	if (!s1 && !s2)
		return (0);
	if ((!s1 && s2) || (s1 && !s2))
		return (-1);
	i = 0;
	while ((*(s1 + i) || *(s2 + i)) && i < n)
	{
		if (((unsigned char)*(s1 + i)) != ((unsigned char)*(s2 + i)))
			return (((unsigned char)*(s1 + i)) - ((unsigned char)*(s2 + i)));
		i++;
	}
	return (0);
}

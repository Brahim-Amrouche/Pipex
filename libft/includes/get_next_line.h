/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:20:27 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/23 12:32:46 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <stddef.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# define GNL_SCOPE 100

size_t	gnl_strlen(char *str);
size_t	gnl_strlcat(char *dst, char *src, size_t dstsize);
void	gnl_strjoin(char **line, char *buffer);
char	*gnl_substr(char *s, unsigned int start, size_t len);
char	*get_next_line(int fd);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:52:44 by bamrouch          #+#    #+#             */
/*   Updated: 2023/01/21 20:19:26 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_garbage_collector.h"

int	**xtf(void)
{
	int		**x;
	int		*y;
	char	*v;

	x = ft_malloc(sizeof(int *) * 2, mem_pass_params(1, NULL, 0));
	y = ft_malloc(sizeof(int) * 3, mem_pass_params(1, NULL, 0));
	v = ft_malloc(sizeof(char) * 5, mem_pass_params(2, NULL, 0));
	x[0] = y;
	ft_print_memory();
	ft_free(1, FALSE);
	return (mem_manage_move(mem_pass_params(1, y, 3)), x);
}

int	main(void)
{
	ft_malloc((sizeof(int *) * 5), mem_pass_params(3, NULL, 0));
	ft_print_memory();
}

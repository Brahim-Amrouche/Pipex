/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem_managers_helpers3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:47:22 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/22 18:07:54 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_garbage_collector.h"

void	ft_free_node(uint64_t scope, void *del_mem)
{
	t_list	*memory_scope;
	t_list	*move_node;
	t_list	*temp;

	if (scope == 0 || !del_mem)
		return ;
	memory_scope = mem_find_scope(scope);
	move_node = mem_find_ref_pointers(memory_scope, del_mem);
	if (!move_node || move_node == memory_scope)
		return ;
	mem_cut_node(memory_scope, move_node);
	while (move_node->content)
	{
		temp = ((t_list *)move_node->content)->next;
		free(((t_list *)move_node->content)->content);
		move_node->content = temp;
	}
	free(move_node);
	if (!((t_list *)memory_scope->content)->next)
		ft_free(scope, FALSE);
}

void	mem_scope_merge(uint64_t scope, uint64_t merge_scope)
{
	t_list	*memory_scope;
	t_list	*move_scope;
	t_list	*moving_nodes;

	if (scope == 0 || merge_scope == 0)
		return ;
	memory_scope = mem_find_scope(scope);
	if (!memory_scope)
		return ;
	move_scope = mem_find_scope(merge_scope);
	if (!move_scope)
		move_scope = mem_add_new_scope(merge_scope);
	moving_nodes = ((t_list *)memory_scope->content)->next;
	move_scope = move_scope->content;
	ft_lstadd_back(&move_scope, moving_nodes);
	((t_list *)memory_scope->content)->next = NULL;
	ft_free(scope, FALSE);
}

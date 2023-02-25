/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garbage_collector.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:19:27 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/22 20:51:24 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GARBAGE_COLLECTOR_H
# define FT_GARBAGE_COLLECTOR_H
# include "ft_printf.h"
# include "get_next_line.h"
// #include "get_next_line_bonus.h"
# include "libft.h"

typedef struct s_mem_manage_params
{
	t_list			*node;
	uint64_t		scope;
	void			*ref_pointer;
	uint64_t		move_scope;
}					t_mem_manage_params;

void				*ft_malloc(uint64_t size, t_mem_manage_params params);
void				ft_free(uint64_t scope, t_boolean purge_all);
void				ft_free_node(uint64_t scope, void *del_mem);
void				mem_move(t_mem_manage_params params);
void				mem_scope_merge(uint64_t scope, uint64_t merge_scope);

// helpers
t_list				*create_node_with_content(void *content);
void				ft_print_memory(void);
t_list				*mem_add_new_scope(uint64_t scope);
t_list				*mem_find_ref_pointers(t_list *memory_scope,
						void *ref_pointer);
t_list				*mem_find_scope(uint64_t scope);
void				mem_cut_node(t_list *memory_scope, t_list *to_cut_node);
t_list				**memory_root(void);
void				mem_free_scope(void *scope_lst);
void				mem_purge_memory(void);

// mem management functions;
t_mem_manage_params	mem_pass_params(uint64_t scope, ...);
t_boolean			mem_manage_add(t_mem_manage_params params);

#endif
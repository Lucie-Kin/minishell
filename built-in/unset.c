/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:14:42 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/21 16:36:01 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	node_clear(t_list *node)
{
	t_list	*tmp_p;
	t_list	*tmp_n;

	tmp_p = node->prev;
	tmp_n = node->next;
	tmp_p->next = tmp_n;
	tmp_n->prev = tmp_p;
	free(node->key);
	free(node->value);
	free(node);
}

void	bigerrno_unset(t_list **env2, char **arg)
{
	int		n;
	t_list	*node;

	n = 1;
	while (arg[n])
	{
		node = find_key(env2, arg[n]);
		if (node)
			node_clear(node);
		n++;
	}
}

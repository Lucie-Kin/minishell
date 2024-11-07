/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:14:42 by lchauffo          #+#    #+#             */
/*   Updated: 2024/11/07 18:18:01 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	node_clear(t_env *node)
{
	t_env	*tmp_p;
	t_env	*tmp_n;

	tmp_p = node->prev;
	tmp_n = node->next;
	if (tmp_p)
		tmp_p->next = tmp_n;
	if (tmp_n)
		tmp_n->prev = tmp_p;
	free(node->key);
	if (node->withvalue == TRUE)
		free(node->value);
	free(node);
}

int	bigerrno_unset(t_env **env, char **arg)
{
	int		n;
	t_env	*node;

	n = 1;
	while (arg[n])
	{
		node = find_key(*env, arg[n]);
		if (node)
			node_clear(node);
		n++;
	}
	return (0);
}

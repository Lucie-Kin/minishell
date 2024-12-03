/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:14:42 by lchauffo          #+#    #+#             */
/*   Updated: 2024/12/03 23:22:54 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	node_clear(t_env *node);

int	bigerrno_unset(t_sh *sh, char **arg)
{
	int		n;
	t_env	*node;

	n = 1;
	while (arg[n])
	{
		node = find_key(&sh->env, arg[n]);
		if (node == sh->env)
			sh->env = node->next;
		if (!node && ft_strcmp(arg[n], "OLDPWD") == 0)
		{
			node = find_key(&sh->hidden, arg[n]);
			if (node && node == sh->hidden)
				sh->hidden = node->next;
		}
		if (node)
			node_clear(node);
		n++;
	}
	return (0);
}

static void	node_clear(t_env *node)
{
	t_env	*tmp_p;
	t_env	*tmp_n;

	if (!node)
		return ;
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

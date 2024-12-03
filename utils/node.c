/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:47:30 by libousse          #+#    #+#             */
/*   Updated: 2024/12/03 18:47:48 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*add_node(t_env **lst, char *key, char *value)
{
	t_env	*new;

	new = lst_new(key, value);
	if (!new || !new->key)
	{
		if (new)
			free(new);
		return (lst_clear(lst), NULL);
	}
	lstadd_back(lst, new);
	return (new);
}

void	clear_node(t_env *node)
{
	if (!node)
		return ;
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

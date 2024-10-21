/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:43:54 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/18 13:44:37 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lst_clear(t_list **lst)
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->key);
		free((*lst)->value);
		free(*lst);
		*lst = tmp;
	}
}

void	clear_node(t_list *node)
{
	if (node->prev == NULL)
	{
		if (node->next == NULL)
			lst_clear(&node);
		else
			node->next->prev = NULL;
	}
	else
	{
		if (node->next == NULL)
			node->prev->next = NULL;
		else
		{
			node->prev->next = node->next;
			node->next->prev = node->prev;
		}
	}
	free(node->key);
	free(node->value);
	free(node);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:21:27 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/18 13:44:26 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*lst_last(t_list *last)
{
	if (!last)
		return (NULL);
	while (last->next)
		last = last->next;
	return (last);
}

t_list	*lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!new)
		return (NULL);
	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return (*lst);
	}
	tmp = lst_last(*lst);
	tmp->next = new;
	new->prev = tmp;
	return (*lst);
}

t_list	*lst_new(char *key, char *value)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	node->key = key;
	node->value = value;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

int	list_size(t_list **lst)
{
	int		size;
	t_list	*loc;

	size = 0;
	loc = *lst;
	while (loc)
	{
		size++;
		loc = loc->next;
	}
	return (size);
}

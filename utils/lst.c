/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:21:27 by lchauffo          #+#    #+#             */
/*   Updated: 2024/12/03 23:20:37 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*lst_last(t_env *last);

t_env	*lst_new(const char *key, const char *value)
{
	t_env	*node;

	if (!key)
		return (NULL);
	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	node->withvalue = (value != NULL);
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_env	*lstadd_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

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

int	lst_size(t_env **lst)
{
	int		size;
	t_env	*loc;

	size = 0;
	loc = *lst;
	while (loc)
	{
		size++;
		loc = loc->next;
	}
	return (size);
}

void	lst_clear(t_env **lst)
{
	t_env	*current;
	t_env	*next;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	*lst = NULL;
}

static t_env	*lst_last(t_env *last)
{
	if (!last)
		return (NULL);
	while (last->next)
		last = last->next;
	return (last);
}

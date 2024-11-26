/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:21:27 by lchauffo          #+#    #+#             */
/*   Updated: 2024/11/25 17:45:06 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*lst_last(t_env *last)
{
	if (!last)
		return (NULL);
	while (last->next)
		last = last->next;
	return (last);
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

int	list_size(t_env **lst)
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

t_env	*list_dup(t_env *src)
{
	t_env	*to_copy;
	t_env	*dup;
	t_env	*node;
	int		len;
	int		i;

	to_copy = src;
	dup = NULL;
	len = list_size(&src);
	i = 0;
	while (to_copy && i < len)
	{
		node = add_node(&dup, to_copy->key, to_copy->value);
		if (!node)
		{
			lst_clear(&dup);
			return (NULL);
		}
		to_copy = to_copy->next;
		i++;
	}
	return (dup);
}

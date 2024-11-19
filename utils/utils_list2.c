/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:41:36 by lchauffo          #+#    #+#             */
/*   Updated: 2024/11/19 16:42:25 by lchauffo         ###   ########.fr       */
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

t_env	*find_key(t_env *env, char *key)
{
	t_env	*list;

	list = env;
	if (!key || !list)
		return (NULL);
	while (list)
	{
		if (bn_isstrstr(list->key, key) == TRUE)
			return (list);
		list = list->next;
	}
	return (NULL);
}

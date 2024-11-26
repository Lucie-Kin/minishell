/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:41:36 by lchauffo          #+#    #+#             */
/*   Updated: 2024/11/26 15:48:21 by lchauffo         ###   ########.fr       */
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

t_env	*find_key(t_env **lst, char *key)
{
	t_env	*tmp;

	if (!key || !lst || !*lst)
		return (NULL);
	tmp = *lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

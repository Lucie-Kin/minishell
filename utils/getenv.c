/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:31:53 by lchauffo          #+#    #+#             */
/*   Updated: 2024/12/03 18:33:14 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*get_var_value(t_sh *sh, char *key)
{
	t_env	*var;

	var = NULL;
	if (sh->hidden)
		var = find_key(&sh->hidden, key);
	if (!var && sh->env)
		var = find_key(&sh->env, key);
	if (var)
		return (var->value);
	return (NULL);
}

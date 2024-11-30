/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:34:52 by lchauffo          #+#    #+#             */
/*   Updated: 2024/11/30 21:36:22 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	manage_env(t_env **hidden, t_env *env_var, t_env *current,
char **append_value)
{
	if (env_var->key[ft_strlen(env_var->key) - 1] == '+')
		*append_value = ft_strjoin(env_var->value, current->value);
	if (env_var->value)
	{
		free(env_var->value);
		env_var->value = NULL;
	}
	if (*append_value)
		env_var->value = *append_value;
	else
		env_var->value = ft_strdup(current->value);
	env_var->withvalue = TRUE;
	if (current == *hidden)
		*hidden = current->next;
	clear_node(current);
}

void	update_env(t_env **env, t_env **hidden)
{
	t_env	*current;
	t_env	*next;
	t_env	*env_var;
	char	*append_value;

	if (!hidden || !*hidden)
		return ;
	current = *hidden;
	append_value = NULL;
	while (current)
	{
		next = current->next;
		env_var = find_key(env, current->key);
		if (env_var && ft_strcmp(current->key, "_") != 0)
			manage_env(hidden, env_var, current, &append_value);
		current = next;
	}
}

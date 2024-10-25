/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:14:22 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/25 19:09:52 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_or_update_var(t_env **env, char *key_value)
{
	t_env	*var;
	char	*key;
	int		separator;

	separator = bn_firstocc(key_value, '=');
	if (separator > 0 && key_value[separator - 1] == '+')
		key = bn_strldup(key_value, separator - 1);
	else if (separator > 0)
		key = bn_strldup(key_value, separator);
	else
		key = ft_strdup(key_value);
	var = find_key(*env, key, TRUE);
	if (var && separator > 0 && key_value[separator - 1] == '+')
	{
		var->value = ft_strjoin(var->value,
				get_literal_token(key_value + separator + 1));
		var->withvalue = TRUE;
	}
	else if (var && separator > 0)
	{
		if (var->value == NULL)
			free(var->value);
		var->value = ft_strdup(get_literal_token(key_value + separator + 1));
		var->withvalue = TRUE;
	}
	else if (var)
		;
	else if (separator > 0)
		add_node(env, key, get_literal_token(key_value + separator + 1));
	else
		add_node(env, key, NULL);
}

char	**parse_key_value(char *to_separate)
{
	char	*separator;
	char	**key_value;
	int		end;

	if (!to_separate)
		return (NULL);
	separator = ft_strchr(to_separate, '=');
	if (separator)
		*separator = ';';
	else
	{
		key_value = ft_calloc(sizeof(char *), 2);
		key_value[0] = ft_strdup(to_separate);
		return (key_value);
	}
	end = ft_strlen(to_separate);
	if (separator == &to_separate[end])
	{
		key_value = ft_calloc(sizeof(char *), 2);
		key_value[0] = ft_strdup(to_separate);
		key_value[1] = ft_strdup("");
	}
	else
		key_value = ft_split(to_separate, ';');
	return (key_value);
}
//t_struct invisible_env >> key=0 -> value=readline(first entry);
// ./minishell or /directory/minishell == argv(0)
//gérer if in readline '=', then add new entry
//when bash, increment SHLVL++ !!!

t_env	*update_var(t_env **hidden, t_env *var, t_env **start)
{
	t_env	*tmp;
	int		size;

	size = ft_strlen((*hidden)->key);
	if ((*hidden)->key[size] == '+')
		var->value = ft_strjoin(var->value, (*hidden)->value);
	else
	{
		free(var->value);
		var->value = ft_strdup((*hidden)->value);
	}
	var->withvalue = TRUE;
	if (*hidden == *start)
		*start = (*hidden)->next;
	tmp = (*hidden)->next;
	clear_node(*hidden);
	return (tmp);
}

void	update_env(t_env **env, t_env **hidden)
{
	t_env	*start;
	t_env	*var;

	if (!hidden)
		return (perror("Nothing to update from hidden"));
	start = *hidden;
	while (*hidden)
	{
		var = find_key(*env, (*hidden)->key, TRUE);
		if (ft_strcmp((*hidden)->key, "_") != 0 && var)
			*hidden = update_var(hidden, var, &start);
		else
			*hidden = (*hidden)->next;
	}
	*hidden = start;
}

void	bigerrno_export(t_env **env, t_env **hidden, t_env **local, char **arg)
{
	t_env	*alpha_order;
	int		n;

	n = 1;
	(void)hidden;
	(void)local;
	// update_env(env, hidden);
	// update_env(env, local);
	alpha_order = alpha_order_list(env);
	if (bn_linelen(arg) == 1)
		print_list(&alpha_order, TRUE);
	else
	{
		while (arg[n])
		{
			if (valid_keyvalue(arg[n]) == TRUE)
				add_or_update_var(env, arg[n]);
			else
				printf("%s 2\n", ERR_EXPORT);
			n++;
		}
	}
	lst_clear(&alpha_order);
	lst_clear(local);
}

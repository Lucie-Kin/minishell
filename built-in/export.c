/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:14:22 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/21 19:09:44 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_or_update_var(t_list **env2, char **key_value)
{
	t_list	*var;
	char	*key;
	int		size;

	size = ft_strlen(key_value[0]);
	key = ft_strdup(key_value[0]);
	if (key_value[1] && key_value[0][size] == '+')
	{
		free(key);
		key = bn_strldup(key_value[0], size - 1);
	}
	var = find_key(env2, key);
	if (var && key_value[1] && key_value[0][size] == '+' && var->value)
		var->value = ft_strjoin(var->value, get_literal_token(key_value[1]));
	else if (var && key_value[1])
	{
		free(var->value);
		var->value = ft_strdup(get_literal_token(key_value[1]));
	}
	else if (key_value[1])
		add_node(env2, key_value[0], get_literal_token(key_value[1]));
	else
		perror(ERR_EXPORT);
	if (var->value)
		var->withvalue = TRUE;
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
	end = ft_strlen(to_separate);
	if (separator == &to_separate[end])
	{
		key_value = ft_calloc(sizeof(char *), 2);
		key_value[0] = ft_strdup(to_separate);
	}
	else
		key_value = ft_split(to_separate, ';');
	return (key_value);
}
//t_struct invisible_env >> key=0 -> value=readline(first entry);
// ./minishell or /directory/minishell == argv(0)
//gérer if in readline '=', then add new entry
//when bash, increment SHLVL++ !!!

t_list	*update_var(t_list **hidden, t_list *var, t_list **start)
{
	t_list	*tmp;
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

void	update_env(t_list **env2, t_list **hidden)
{
	t_list	*start;
	t_list	*var;

	if (!hidden)
		return ;
	start = *hidden;
	while (*hidden)
	{
		var = find_key(env2, (*hidden)->key);
		if (ft_strcmp((*hidden)->key, "_") != 0 && var)
			*hidden = update_var(hidden, var, &start);
		else
			*hidden = (*hidden)->next;
	}
	*hidden = start;
}

void	bigerrno_export(t_list **env2, t_list **hidden, char **arg)
{
	t_list	*alpha_order;
	char	**key_value;
	int		n;

	n = 0;
	update_env(env2, hidden);
	alpha_order = alpha_order_list(env2);
	if (!arg[1])
		print_list(&alpha_order, TRUE);
	else
	{
		while (arg[1 + n])
		{
			key_value = parse_key_value(arg[1 + n]);
			if (key_value[2])
				perror(ERR_EXPORT);
			else if (valid_keyvalue(key_value[0], key_value[1]) == TRUE)
				add_or_update_var(env2, key_value);
			else
				perror(ERR_EXPORT);
			bn_freetab(key_value);
			n++;
		}
	}
	lst_clear(&alpha_order);
}

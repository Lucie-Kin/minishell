/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:14:22 by lchauffo          #+#    #+#             */
/*   Updated: 2024/12/05 12:41:26 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_lst(t_env **lst, int export);
static void	add_or_update_var(t_env **env, char *key_value);
static void	update_var(t_env *var, char *key_value, int separator);
static char	*extract_key(int separator, char *key_value);
static void	switch_key_to_localvar(char **onlykey, t_env **local);

int	bigerrno_export(t_env **env, t_env **hidden, t_env **local, char **arg)
{
	t_env	*alpha_order;
	int		n;

	n = 1;
	update_env(env, hidden);
	alpha_order = alpha_order_lst(env);
	if (get_array_length((void **)arg) == 1)
		print_lst(&alpha_order, TRUE);
	else
	{
		while (arg[n])
		{
			switch_key_to_localvar(&arg[n], local);
			if (valid_keyvalue(arg[n]) == TRUE)
				add_or_update_var(env, arg[n]);
			else
				output_error(EPERM,
					compose_err_msg(SHELL, "export", arg[n], ERR_EXPORT));
			n++;
		}
	}
	lst_clear(&alpha_order);
	lst_clear(local);
	return (0);
}

static void	switch_key_to_localvar(char **onlykey, t_env **local)
{
	t_env	*tmp;
	char	*compose;

	tmp = *local;
	if (!local || !*local || !onlykey || !*onlykey)
		return ;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, *onlykey) == 0)
		{
			free(*onlykey);
			compose = ft_strjoin(tmp->key, "=");
			*onlykey = ft_strjoin(compose, tmp->value);
			free(compose);
		}
		tmp = tmp->next;
	}
}

static void	print_lst(t_env **lst, int export)
{
	t_env	*tmp;

	tmp = *lst;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (export == TRUE)
		{
			if (ft_strcmp(tmp->key, "_") == 0)
				;
			else if (tmp->withvalue == TRUE)
				printf("%s %s=\"%s\"\n", MSG_EXPORT, tmp->key, tmp->value);
			else
				printf("%s %s\n", MSG_EXPORT, tmp->key);
		}
		else
		{
			if (tmp->withvalue == TRUE)
				printf("%s=%s\n", tmp->key, tmp->value);
		}
		tmp = tmp->next;
	}
}

static void	add_or_update_var(t_env **env, char *key_value)
{
	t_env	*var;
	char	*key;
	char	*value;
	int		separator;

	separator = firstocc(key_value, '=');
	key = extract_key(separator, key_value);
	var = find_key(env, key);
	if (var)
	{
		if (var->withvalue == TRUE)
			update_var(var, key_value, separator);
	}
	else if (separator > 0)
	{
		value = get_literal_token(key_value + separator + 1);
		add_node(env, key, value);
		free(value);
	}
	else
		add_node(env, key_value, NULL);
	free(key);
}

static void	update_var(t_env *var, char *key_value, int separator)
{
	char	*tmp_value;
	char	*tmp_newvalue;

	if (separator > 0 && key_value[separator - 1] == '+')
	{
		tmp_newvalue = get_literal_token(key_value + separator + 1);
		tmp_value = ft_strjoin(var->value, tmp_newvalue);
		free(var->value);
		free(tmp_newvalue);
		var->value = tmp_value;
		var->withvalue = TRUE;
	}
	else if (separator > 0)
	{
		if (var->value != NULL)
			free(var->value);
		var->value = get_literal_token(key_value + separator + 1);
		var->withvalue = TRUE;
	}
}

static char	*extract_key(int separator, char *key_value)
{
	if (separator > 0 && key_value[separator - 1] == '+')
		return (ft_substr(key_value, 0, separator - 1));
	else if (separator > 0)
		return (ft_substr(key_value, 0, separator));
	return (ft_strdup(key_value));
}

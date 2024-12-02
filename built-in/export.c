/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:14:22 by lchauffo          #+#    #+#             */
/*   Updated: 2024/12/02 15:57:12 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_var(t_env *var, char *key_value, int separator)
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
		return (bn_strldup(key_value, separator - 1));
	else if (separator > 0)
		return (bn_strldup(key_value, separator));
	return (ft_strdup(key_value));
}

void	add_or_update_var(t_env **env, char *key_value)
{
	t_env	*var;
	char	*key;
	char	*value;
	int		separator;

	separator = bn_firstocc(key_value, '=');
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

int	bigerrno_export(t_env **env, t_env **hidden, t_env **local, char **arg)
{
	t_env	*alpha_order;
	int		n;

	n = 1;
	update_env(env, hidden);
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
				output_error(EPERM,
					compose_err_msg(SHELL, "export", arg[n], ERR_EXPORT));
			n++;
		}
	}
	lst_clear(&alpha_order);
	lst_clear(local);
	return (0);
}

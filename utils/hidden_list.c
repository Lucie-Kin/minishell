/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hidden_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:37:36 by lchauffo          #+#    #+#             */
/*   Updated: 2024/11/26 12:56:39 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	only_var(char **arg)
{
	int		i;

	i = 0;
	if (!arg || !(*arg))
		return (FALSE);
	while (arg[i])
	{
		if (ft_strchr(arg[i], '=') == NULL)
			return (FALSE);
		else if (valid_keyvalue(arg[i]) == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}
void	update_value(t_env *found_node, char *key, char *value, int is_append)
{
	char *joined;

	if (is_append && found_node->value)
	{
		joined = ft_strjoin(found_node->value, value);
		free(found_node->value);
		found_node->value = joined;
		free(key);
		free(value);
	}
	else
	{
		if (found_node->value)
			free(found_node->value);
		found_node->value = value;
		free(key);
	}
}

void process_token(t_env **hidden, char *token)
{
	t_env *found_node;
	t_env *node;
	int first_equal_occurence;
	int is_append;
	char	*key_value[2];
	
	first_equal_occurence = bn_firstocc(token, '=');
	is_append = token[first_equal_occurence - 1] == '+';
	key_value[0] = bn_strldup(token, first_equal_occurence - is_append);
	key_value[1] = ft_strdup(token + first_equal_occurence + 1);
	found_node = find_key(hidden, key_value[0]);
	if (found_node)
		update_value(found_node, key_value[0], key_value[1], is_append);
	else
	{
		node = lst_new(key_value[0], key_value[1]);
		free(key_value[0]);
		free(key_value[1]);
		lstadd_back(hidden, node);
	}
}

void	update_hidden(t_env **hidden, char **token)
{
	int	i;

	i = 0;
	if (!token)
		return ;
	while (token[i])
	{
		process_token(hidden, token[i]);
		++i;
	}
	// print_list(hidden, false);
}

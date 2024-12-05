/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:16:37 by libousse          #+#    #+#             */
/*   Updated: 2024/12/05 13:11:09 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_local(char ***cmd, t_env **local, int *i);
static char	**parse_key_value(char *to_separate);
static int	add_local(t_env **local, char **key_value);

void	extract_local_update(char ***cmd, t_env **local)
{
	int	i;

	i = 0;
	if (!cmd || !(*cmd) || !(**cmd))
		return ;
	update_local(cmd, local, &i);
	if (i > 0)
		remove_array_elements((void **)(*cmd), 0, i - 1, free);
}

static int	add_local(t_env **local, char **key_value)
{
	t_env	*new;

	new = lst_new(key_value[0], key_value[1]);
	free_entire_array((void **)key_value, free);
	if (!new)
	{
		lst_clear(local);
		return (-1);
	}
	lstadd_back(local, new);
	return (0);
}

static void	update_local(char ***cmd, t_env **local, int *i)
{
	char	**key_value;
	t_env	*node;

	while ((*cmd)[*i])
	{
		if (ft_strchr((*cmd)[*i], '=') == 0 ||
		valid_keyvalue((*cmd)[*i]) == FALSE)
			break ;
		key_value = parse_key_value((*cmd)[*i]);
		node = find_key(local, key_value[0]);
		if (node)
		{
			free(node->value);
			node->value = ft_strdup(key_value[1]);
			free_entire_array((void **)key_value, free);
		}
		else if (key_value)
		{
			if (add_local(local, key_value) == -1)
				break ;
		}
		(*i)++;
	}
}

static char	**parse_key_value(char *to_separate)
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
		key_value = ft_calloc(2, sizeof(char *));
		key_value[0] = ft_strdup(to_separate);
		return (key_value);
	}
	end = ft_strlen(to_separate);
	if (separator == &to_separate[end])
	{
		key_value = ft_calloc(2, sizeof(char *));
		key_value[0] = ft_strdup(to_separate);
		key_value[1] = ft_strdup("");
	}
	else
		key_value = ft_split(to_separate, ';');
	return (key_value);
}

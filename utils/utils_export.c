/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:56:49 by lchauffo          #+#    #+#             */
/*   Updated: 2024/11/23 17:17:52 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	swap_p(char **to_be_swap, char **swap_with)
{
	char	*tmp;

	tmp = *to_be_swap;
	*to_be_swap = *swap_with;
	*swap_with = tmp;
}

void	swap_node_content(t_env *s1, t_env *s2)
{
	int		tmp_bool;
	char	*tmp_key;
	char	*tmp_value;

	tmp_bool = s1->withvalue;
	s1->withvalue = s2->withvalue;
	s2->withvalue = tmp_bool;
	tmp_key = s1->key;
	s1->key = s2->key;
	s2->key = tmp_key;
	tmp_value = s1->value;
	s1->value = s2->value;
	s2->value = tmp_value;
}

int	valid_keyvalue(char *key_value)
{
	int		i;
	int		separator;

	i = 0;
	separator = bn_firstocc(key_value, '=');
	if (key_value[0] == '_' && (!key_value[1] || separator == 1))
		return (FALSE);
	else if (ft_isdigit(key_value[0]) == TRUE)
		return (FALSE);
	else if (ft_isalpha(key_value[i]) == TRUE || key_value[i] == '_')
	{
		while (key_value[i] && (separator == -1 || i < separator - !!i))
		{
			if (!(ft_isalnum(key_value[i]) == TRUE || key_value[i] == '_'))
				return (FALSE);
			i++;
		}
		if (ft_isalnum(key_value[i]) == TRUE
			|| key_value[i] == '_' || key_value[i] == '+')
		{
			if (separator == -1 && key_value[i] == '+')
				return (FALSE);
			return (TRUE);
		}
	}
	else
		return (FALSE);
	return (TRUE);
}

void	print_list(t_env **list, int export)
{
	t_env	*tmp;

	tmp = *list;
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

t_env	*alpha_order_list(t_env **env)
{
	t_env	*start;
	t_env	*ordered;
	int		swapped;

	if (!*env)
		return (NULL);
	start = list_dup(*env);
	if (!start)
		return (NULL);
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ordered = start;
		while (ordered->next)
		{
			if (ft_strcmp(ordered->key, ordered->next->key) > 0)
			{
				swap_node_content(ordered, ordered->next);
				swapped = 1;
			}
			ordered = ordered->next;
		}
	}
	return (start);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:56:49 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/25 18:19:37 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	swap_str(char **to_be_swap, char **swap_with)
{
	char	*tmp;

	tmp = *to_be_swap;
	*to_be_swap = ft_strdup((const char *)*swap_with);
	if (*to_be_swap == NULL)
		return ;
	*swap_with = ft_strdup((const char *)tmp);
	free(tmp);
}

void	swap_node_content(t_env **s1, t_env **s2)
{
	int	tmp;

	tmp = (*s1)->withvalue;
	(*s1)->withvalue = (*s2)->withvalue;
	(*s2)->withvalue = tmp;
	swap_str(&(*s1)->key, &(*s2)->key);
	swap_str(&(*s1)->value, &(*s2)->value);
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
		while (key_value[i] && (separator == -1 || i < separator - 1))
		{
			if (!(ft_isalnum(key_value[i]) == TRUE || key_value[i] == '_'))
				return (FALSE);
			i++;
		}
		if (ft_isalnum(key_value[i]) == TRUE || key_value[i] == '_' || key_value[i] == '+')
		{
			if (separator == -1 && key_value[i] == '+')
				return (FALSE);
			return (TRUE);
		}
	}
	return (TRUE);
}

void	print_list(t_env **list, int export)
{
	t_env	*tmp;

	tmp = *list;
	if (!tmp)
		perror("Failure to read env");
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
	{
		fprintf(stderr, "env is empty\n");
		return (NULL);
	}
	start = list_dup(*env);
	if (!start)
	{
		fprintf(stderr, "Duplication failed\n");
		return (NULL);
	}
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ordered = start;
		while (ordered->next)
		{
			if (ft_strcmp(ordered->key, ordered->next->key) > 0)
			{
				swap_node_content(&ordered, &ordered->next);
				swapped = 1;
			}
			ordered = ordered->next;
		}
	}
	return (start);
}

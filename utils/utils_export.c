/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:56:49 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/24 19:58:25 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	swap_param(void **to_be_swap, void **swap_with)
{
	void	*tmp;

	tmp = *to_be_swap;
	*to_be_swap = *swap_with;
	*swap_with = tmp;
}

void	swap_node_content(t_env **s1, t_env **s2)
{
	swap_param((void **)(*s1)->key, (void **)(*s2)->key);
	swap_param((void **)(*s1)->value, (void **)(*s2)->value);
}

int	valid_keyvalue(char *key, char *value)
{
	int	i;
	int	end;

	i = 0;
	end = ft_strlen(key);
	if (key[0] == '_' && !key[1])
		return (FALSE);
	else if (ft_isdigit(key[0]) == TRUE)
		return (FALSE);
	else if (ft_isalpha(key[0]) == TRUE || key[0] == '_')
	{
		while (key[++i] && i < end)
		{
			if (!(ft_isalnum(key[i]) == TRUE || key[i] == '_'))
				return (FALSE);
		}
		if (ft_isalnum(key[++i]) == TRUE || key[i] == '_' || key[i] == '+')
		{
			if (!value && key[i] == '+')
				return (FALSE);
			return (TRUE);
		}
	}
	return (FALSE);
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
			if (tmp->withvalue == TRUE)
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

	start = *env;
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
				swap_node_content(&ordered, &ordered->next);
				swapped = 1;
			}
			ordered = ordered->next;
		}
	}
	return (start);
}

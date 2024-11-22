/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hidden_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:37:36 by lchauffo          #+#    #+#             */
/*   Updated: 2024/11/22 17:17:47 by lchauffo         ###   ########.fr       */
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
	dprintf(2, "TRUE\n");
	return (TRUE);
}

void	update_hidden(t_env **hidden, char **token)
{
	t_env	*node;
	char	*key;
	int		size;
	int		i;

	if (!token || !hidden)
		return ;
	i = -1;
	while (token[++i])
	{
		size = bn_firstocc(token[i], '=');
		if (size != -1)
		{
			key = bn_strldup(token[i], size - (token[i][size - 1] == '+'));
			if (hidden && find_key(*hidden, key))
			{
				node = find_key(*hidden, key);
				if (node->value)
					free(node->value);
				node->value = ft_strdup(token[i] + size + 1);
				node->withvalue = TRUE;
				free(key);
			}
			else
			{
				node = lst_new(key, token[i] + size + 1);
				free(key);
				if (!node)
					return ;
			}
			lstadd_back(hidden, node);
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hidden_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:37:36 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/25 15:24:54 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	only_var(char **arg)
{
	int		i;

	i = 0;
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

void	update_hidden(t_env **hidden, char **token)
{
	t_env	*new;
	char	*key;
	char	*value;
	int		size;
	int		i;

	if (!token)
		return ;
	i = 0;
	while (token[i])
	{
		size = bn_firstocc(token[i], '=');
		if (size != -1)
		{
			key = bn_strldup(token[i], size);
			if (size != (int)ft_strlen(token[i]))
				value = ft_strdup(token[i] + size + 1);
			else
				value = ft_strdup("");
			new = lst_new(key, value);
			lstadd_back(hidden, new);
		}
		i++;
	}
}

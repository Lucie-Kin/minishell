/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hidden_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:37:36 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/23 19:15:37 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	only_var(char **arg)
{
	char	**key_value;
	int		i;
	int		status;

	i = 0;
	status = TRUE;
	while (arg[i])
	{
		key_value = parse_key_value(arg[i]);
		if (bn_linelen(key_value) != 2)
			status = FALSE;
		else if (valid_keyvalue(key_value[0], key_value[1]) == FALSE)
			status = FALSE;
		bn_freetab(key_value);
		i++;
	}
	return (status);
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

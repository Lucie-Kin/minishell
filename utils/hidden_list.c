/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hidden_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:37:36 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/16 18:41:39 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_hidden(t_list **hidden, char *token)
{
	t_list	*new;
	char	*key;
	char	*value;
	int		size;

	if (!token)
		return ;
	size = bn_firstocc(token, '=');
	if (size != -1)
	{
		key = bn_strldup(token, size);
		if (size != ft_strlen(token))
			value = ft_strdup(token + size + 1);
		else
			value = ft_strdup("");
		new = lst_new(key, value);
		lstadd_back(hidden, new);
	}
}

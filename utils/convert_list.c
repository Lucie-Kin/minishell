/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:28:32 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/24 19:55:11 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*convert_to_list(char **env)
{
	t_env	*lst;
	t_env	*new;
	char	*key;
	int		size;
	int		i;

	i = 0;
	lst = NULL;
	while (env[i])
	{
		size = bn_strnlen(env[i], '=');
		key = bn_strldup(env[i], size);
		new = lst_new(key, ft_strdup(getenv(key)));
		if (!new)
			lst_clear(&lst);
		lstadd_back(&lst, new);
		i++;
	}
	return (lst);
}

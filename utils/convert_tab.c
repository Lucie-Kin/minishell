/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:50:07 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/22 14:08:54 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**convert_to_tab(t_env *env)
{
	char	**env_tab;
	char	*tmp;
	int		size;
	int		i;

	size = list_size(&env);
	env_tab = ft_calloc(sizeof(char *), size + 1);
	i = 0;
	while (env)
	{
		tmp = ft_strjoin(env->key, "=");
		env_tab[i++] = ft_strjoin(tmp, env->value);
		free(tmp);
		env = env->next;
	}
	return (env_tab);
}

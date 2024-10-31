/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:31:53 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/29 18:01:53 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_var_value(t_sh *sh, char *key)
{
	t_env	*var;

	var = NULL;
	if (sh->hidden)
		var = find_key(sh->hidden, key, FALSE);
	if (!var && sh->env)
		var = find_key(sh->env, key, FALSE);
	if (var)
		return (var->value);
	return (NULL);
}

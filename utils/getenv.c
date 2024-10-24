/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:31:53 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/24 19:59:53 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env(t_env *env, char *key)
{
	t_env	*var;

	var = find_key(&env, key, TRUE);
	if (var)
		return (var->value);
	return (NULL);
}

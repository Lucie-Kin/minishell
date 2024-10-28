/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:31:53 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/25 19:10:00 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env(t_env *env, char *key)
{
	t_env	*var;

	var = find_key(env, key, TRUE);
	if (var)
		return (var->value);
	return (NULL);
}

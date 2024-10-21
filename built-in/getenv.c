/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:31:53 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/21 18:19:16 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*bigerrno_getenv(t_list **env2, char *key)
{
	t_list	*var;

	var = find_key(env2, key);
	if (var)
		return (var->value);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:03:50 by lchauffo          #+#    #+#             */
/*   Updated: 2025/02/24 13:33:06 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigerrno.h"

void	update_shlvl(t_env **env, int inpipe)
{
	t_env	*var;
	int		shlvl;

	var = find_key(env, "SHLVL");
	if (!var)
	{
		shlvl = 1;
		add_node(env, "SHLVL", "1");
	}
	else
	{
		shlvl = ft_atoi(var->value);
		free(var->value);
		if (inpipe == TRUE)
			shlvl--;
		else
			shlvl++;
		var->value = ft_itoa(shlvl);
	}
}

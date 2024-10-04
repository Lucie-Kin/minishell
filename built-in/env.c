/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:14:16 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/02 17:11:03 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	bigerrno_env(t_list **env2, char **arg, int env)
{
	if (!arg[env + 1])
		print_list(env2, NULL, FALSE);
}

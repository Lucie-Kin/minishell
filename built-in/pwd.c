/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:14:37 by lchauffo          #+#    #+#             */
/*   Updated: 2024/09/28 19:26:49 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	bigerrno_pwd(t_list **env2)
{
	t_list	*pwd;

	pwd = find_key(env2, "PWD");
	if (!pwd)
		perror("Failure get PWD");
	printf("%s\n", pwd->value);
}

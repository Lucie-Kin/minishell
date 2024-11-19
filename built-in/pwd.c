/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:14:37 by lchauffo          #+#    #+#             */
/*   Updated: 2024/11/16 16:04:04 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_pwd(t_sh *sh)
{
	sh->pwd = ft_calloc(sizeof(t_sh), 1);
	sh->pwd->value = getcwd(NULL, 0);
	sh->pwd->key = ft_strdup("PWD");
	sh->pwd->withvalue = TRUE;
	sh->pwd->prev = NULL;
	sh->pwd->next = NULL;
}

int	bigerrno_pwd(t_sh *sh)
{
	char	*str;

	str = getcwd(NULL, 0);
	if (str)
	{
		free(sh->pwd->value);
		sh->pwd->value = str;
	}
	printf("%s\n", sh->pwd->value);
	return (0);
}

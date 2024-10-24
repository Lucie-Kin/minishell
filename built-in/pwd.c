/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:14:37 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/23 22:52:17 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	bigerrno_pwd(void)
{
	char	*str;

	str = getcwd(NULL, 0);
	if (!str)
	{
		perror("Failure getcwd");
		return ;
	}
	printf("%s\n", str);
	free(str);
}

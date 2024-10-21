/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:12:05 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/21 18:41:39 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	bigerrno_exit(char **arg, int *code_error, char **msg)
{
	int	numb;

	*code_error = 0;
	if (arg[1] && arg[2])
	{
		*msg = ft_strdup("bash: exit: too many arguments");
		*code_error = 1;
		return ;
	}
	else if (arg[1])
	{
		numb = ft_atoi(arg[1]);
		if ((numb != 0 || ft_strcmp(arg[1], "0") == 0) == FALSE)
		{
			*msg = ft_strdup
				("bash: exit: invalidvalue: numeric argument required");
			*code_error = 2;
		}
		else
			*code_error = ft_atoi(arg[1]) % 256;
	}
	if (*msg)
		perror(*msg);
	exit (*code_error);
}

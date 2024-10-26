/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:12:05 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/26 17:25:39 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	bigerrno_exit(char **arg, int *code_error, char **msg)
{
	int	numb;

	*code_error = 0;
	printf("exit\n");
	if (bn_linelen(arg) > 2)
	{
		*msg = ft_strdup(compose_err_msg(arg[0], NULL, ERR_NB_ARGS));
		*code_error = 1;
		return ;
	}
	else if (arg[1])
	{
		numb = ft_atoi(arg[1]);
		if ((numb != 0 || ft_strcmp(arg[1], "0") == 0) == FALSE)
		{
			*msg = ft_strdup
				(compose_err_msg(arg[0], arg[1], ERR_NONUM));
			*code_error = 2;
		}
		else
			*code_error = ft_atoi(arg[1]) % 256;
	}
	if (*msg)
		printf("%s", *msg);
	exit (*code_error);
}

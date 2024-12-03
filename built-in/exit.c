/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:12:05 by lchauffo          #+#    #+#             */
/*   Updated: 2024/12/03 23:23:08 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bigerrno_exit(t_sh *sh, char **arg)
{
	int		numb;

	sh->keep_running = FALSE;
	if (sh->subshell == 0)
		printf("exit\n");
	if (get_array_length((void **)arg) > 2)
	{
		return (output_error(1, compose_err_msg
				(SHELL, arg[0], NULL, ERR_NB_ARGS)));
	}
	if (arg[1])
	{
		numb = ft_atoi(arg[1]);
		if ((numb != 0 || ft_strcmp(arg[1], "0") == 0) == FALSE)
			return (output_error(2, compose_err_msg
					(SHELL, arg[0], arg[1], ERR_NONUM)));
		else
			return (ft_atoi(arg[1]) % 256);
	}
	return (sh->exit_code);
}

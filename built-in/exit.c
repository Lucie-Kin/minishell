/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:12:05 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/31 18:22:16 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	bigerrno_exit(t_sh *sh, char **arg)
{
	int		numb;
	char	*msg;

	sh->exit_code = 0;
	msg = 0;
	if (bn_linelen(arg) > 2)
	{
		msg = ft_strdup(compose_err_msg(SHELL, arg[0], 0, ERR_NB_ARGS));
		sh->exit_code = 1;
	}
	else if (arg[1])
	{
		numb = ft_atoi(arg[1]);
		if ((numb != 0 || ft_strcmp(arg[1], "0") == 0) == FALSE)
		{
			msg = ft_strdup(compose_err_msg(SHELL, arg[0], arg[1], ERR_NONUM));
			sh->exit_code = 2;
		}
		else
			sh->exit_code = ft_atoi(arg[1]) % 256;
	}
	if (msg)
		printf("%s", msg);
	free(msg);
	sh->keep_running = FALSE;
	return (sh->exit_code);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:10:30 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/21 18:16:50 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	isbuiltin(t_list **env2, t_list **hidden, char **arg)
{
	int		code_error;
	char	*msg;

	code_error = 0;
	msg = 0;
	if (ft_strcmp(arg[0], "cd") == 0)
		bigerrno_cd(env2, arg);
	else if (ft_strcmp(arg[0], "echo") == 0)
		bigerrno_echo(arg);
	else if (ft_strcmp(arg[0], "env") == 0)
		bigerrno_env(env2, arg);
	else if (ft_strcmp(arg[0], "exit") == 0)
		bigerrno_exit(arg, &code_error, &msg);
	else if (ft_strcmp(arg[0], "export") == 0)
		bigerrno_export(env2, hidden, arg);
	else if (ft_strcmp(arg[0], "pwd") == 0)
		bigerrno_pwd(env2);
	else if (ft_strcmp(arg[0], "unset") == 0)
		bigerrno_unset(env2, arg);
	else
		return (FALSE);
	free(msg);
	return (TRUE);
}

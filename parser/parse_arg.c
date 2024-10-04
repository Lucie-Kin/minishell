/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:10:30 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/02 17:33:46 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	isbuiltin(char **arg, int n)
{
	if (ft_strcmp(arg[n], "cd") == 0)
		return (bigerrno_cd(arg), TRUE);
	else if (ft_strcmp(arg[n], "echo") == 0)
		return (bigerrno_echo(arg, n), TRUE);
	else if (ft_strcmp(arg[n], "env") == 0)
		return (bigerrno_env(arg), TRUE);
	else if (ft_strcmp(arg[n], "exit") == 0)
		return (bigerrno_exit(arg), TRUE);
	else if (ft_strcmp(arg[n], "export") == 0)
		return (bigerrno_export(arg), TRUE);
	else if (ft_strcmp(arg[n], "pwd") == 0)
		return (bigerrno_pwd(arg), TRUE);
	else if (ft_strcmp(arg[n], "unset") == 0)
		return (bigerrno_unset(arg), TRUE);
	return (FALSE);
}

int	iscmd(char **arg, int n)
{
	if (isbuiltin(arg, n))
		return (TRUE);
	else if (isxternal(arg, n))
		return (TRUE);
	else
		return (FALSE);
}

void	parse_arg(char **arg, int n)
{
	if (isinfile() == TRUE)
		return ;
	else if (isoutfile() == TRUE)
		return ;
	else if (iscmd(arg, n) == TRUE)
		return ;
	return ;
}

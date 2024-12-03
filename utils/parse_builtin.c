/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:10:30 by lchauffo          #+#    #+#             */
/*   Updated: 2024/12/03 23:20:46 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_var(char **cmd);

int	isbuiltin(char **cmd)
{
	char	**cmd_arr;
	int		state;
	int		i;
	int		j;

	if (!cmd[0])
		return (FALSE);
	j = skip_var(cmd);
	cmd_arr = ft_split("cd:echo:env:exit:export:pwd:unset:\
	hidden:lulu:shoot", ':');
	state = FALSE;
	i = 0;
	while (cmd[j] && cmd_arr[i])
	{
		if (ft_strcmp(cmd[j], cmd_arr[i]) == 0)
		{
			state = TRUE;
			break ;
		}
		i++;
	}
	free_entire_array((void **)cmd_arr, free);
	return (state);
}

int	execute_builtin(t_sh *sh)
{
	char	**cmdl;
	int		code_err;

	code_err = 0;
	cmdl = sh->ex->pl.cmdl[sh->ex->pl.index];
	extract_local_update(&cmdl, &sh->local);
	if (ft_strcmp(cmdl[0], "cd") == 0)
		code_err = bigerrno_cd(sh, cmdl);
	else if (ft_strcmp(cmdl[0], "echo") == 0)
		code_err = bigerrno_echo(cmdl);
	else if (ft_strcmp(cmdl[0], "env") == 0)
		code_err = bigerrno_env(&sh->env, &sh->hidden, &sh->local, cmdl);
	else if (ft_strcmp(cmdl[0], "exit") == 0)
		code_err = bigerrno_exit(sh, cmdl);
	else if (ft_strcmp(cmdl[0], "export") == 0)
		code_err = bigerrno_export(&sh->env, &sh->hidden, &sh->local, cmdl);
	else if (ft_strcmp(cmdl[0], "pwd") == 0)
		code_err = bigerrno_pwd(sh);
	else if (ft_strcmp(cmdl[0], "unset") == 0)
		code_err = bigerrno_unset(sh, cmdl);
	else
		bigerrno_bonus(sh, cmdl, &code_err);
	return (code_err);
}

static int	skip_var(char **cmd)
{
	int	j;

	j = 0;
	if (!cmd)
		return (0);
	while (cmd[j])
	{
		if (!ft_strchr(cmd[j], '=') || valid_keyvalue(cmd[j]) == FALSE)
			break ;
		j++;
	}
	return (j);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:10:30 by lchauffo          #+#    #+#             */
/*   Updated: 2024/11/20 14:38:18 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_local(char **cmd, t_env **local)
{
	t_env	*new;
	char	**key_value;
	int		i;

	i = 0;
	while (cmd[i])
	{
		key_value = parse_key_value(cmd[i]);
		if (ft_strchr(cmd[i], '=') || valid_keyvalue(cmd[i]) == FALSE)
			break ;
		new = lst_new(key_value[0], key_value[1]);
		lstadd_back(local, new);
		bn_freetab(key_value);
		i++;
	}
	if (key_value)
		bn_freetab(key_value);
	if (i > 0)
		extract_array_elements((void **)cmd, 0, i - 1);
}

int	isbuiltin(char **cmd, t_env *local)
{
	char	**cmd_tab;
	int		state;
	int		i;

	if (!cmd[0])
		return (FALSE);
	(void)local;
	// update_local(cmd, &local);
	cmd_tab = ft_split("cd:echo:env:exit:export:pwd:unset", ':');
	state = FALSE;
	i = 0;
	while (cmd_tab[i])
	{
		if (ft_strcmp(cmd[0], cmd_tab[i]) == 0)
		{
			state = TRUE;
			break ;
		}
		i++;
	}
	bn_freetab(cmd_tab);
	return (state);
}

int	execute_builtin(t_sh *sh)
{
	char	**cmdl;
	int		code_err;

	code_err = 0;
	cmdl = sh->ex->pl.cmdl[sh->ex->pl.index];
	// print_list(&sh->local, TRUE);
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
		code_err = bigerrno_unset(&sh->env, cmdl);
	return (code_err);
}

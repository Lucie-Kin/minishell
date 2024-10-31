/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:10:30 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/29 19:29:22 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_local(char **cmd, t_env **local)//
{
	t_env	*new;
	char	**key_value;
	int		i;

	i = 0;
	while (cmd[i])
	{
		key_value = parse_key_value(cmd[i]);
		if (bn_linelen(key_value) != 2)
			break ;
		else if (ft_strchr(cmd[i], '=') || valid_keyvalue(cmd[i]) == FALSE)
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

// Upgrade error management
// 
int	execute_builtin(t_sh *sh)
{
	char	**cmdl;

	cmdl = sh->ex->pl.cmdl[sh->ex->pl.index];
	if (ft_strcmp(cmdl[0], "cd") == 0)
		return (bigerrno_cd(&sh->env, &sh->local, cmdl));
	else if (ft_strcmp(cmdl[0], "echo") == 0)
		return (bigerrno_echo(cmdl));
	else if (ft_strcmp(cmdl[0], "env") == 0)
		return (bigerrno_env(&sh->env, &sh->local, cmdl));
	else if (ft_strcmp(cmdl[0], "exit") == 0)
		return (bigerrno_exit(sh, cmdl));
	else if (ft_strcmp(cmdl[0], "export") == 0)
		return (bigerrno_export(&sh->env, &sh->hidden, &sh->local, cmdl));
	else if (ft_strcmp(cmdl[0], "pwd") == 0)
		return (bigerrno_pwd());
	else if (ft_strcmp(cmdl[0], "unset") == 0)
		return (bigerrno_unset(&sh->env, cmdl));
	return (0);
}

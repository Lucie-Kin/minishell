/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:10:30 by lchauffo          #+#    #+#             */
/*   Updated: 2024/11/25 16:01:13 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_local(char ***cmd, t_env **local)
{
	t_env	*new;
	char	**key_value;
	int		i;
	void	**extracted;

	i = 0;
	if (!cmd || !(*cmd) || !(**cmd))
		return ;
	while ((*cmd)[i])
	{
		if (ft_strchr((*cmd)[i], '=') == 0 ||
		valid_keyvalue((*cmd)[i]) == FALSE)
			break ;
		key_value = parse_key_value((*cmd)[i]);
		if (key_value)
		{
			new = lst_new(key_value[0], key_value[1]);
			free_entire_array((void **)key_value, free);
			if (!new)
			{
				lst_clear(local);
				break ;
			}
			lstadd_back(local, new);
		}
		i++;
	}
	if (i > 0)
	{
		extracted = extract_array_elements((void **)(*cmd), 0, i - 1);
		free_entire_array(extracted, NULL);
	}
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

int	isbuiltin(char **cmd)
{
	char	**cmd_tab;
	int		state;
	int		i;
	int		j;

	if (!cmd[0])
		return (FALSE);
	j = skip_var(cmd);
	cmd_tab = ft_split("cd:echo:env:exit:export:pwd:unset:hidden", ':');
	state = FALSE;
	i = 0;
	while (cmd[j] && cmd_tab[i])
	{
		if (ft_strcmp(cmd[j], cmd_tab[i]) == 0)
		{
			state = TRUE;
			break ;
		}
		i++;
	}
	free_entire_array((void **)cmd_tab, free);
	return (state);
}

int	execute_builtin(t_sh *sh)
{
	char	**cmdl;
	int		code_err;

	code_err = 0;
	cmdl = sh->ex->pl.cmdl[sh->ex->pl.index];
	update_local(&cmdl, &sh->local);
	// print_list(&sh->hidden, FALSE);
	// print_list(&sh->local, FALSE);
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
	else if (ft_strcmp(cmdl[0], "hidden") == 0)
		code_err = bigerrno_hidden(&sh->hidden, cmdl);
	lst_clear(&sh->local);
	return (code_err);
}

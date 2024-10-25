/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:10:30 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/25 19:15:22 by lchauffo         ###   ########.fr       */
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
	char	*cmd_str;
	char	**cmd_tab;
	int		state;
	int		i;

	(void)local;
	// update_local(cmd, &local);
	cmd_str = ft_strdup("cd:echo:env:exit:export:pwd:unset");
	cmd_tab = ft_split(cmd_str, ':');
	free(cmd_str);
	state = FALSE;
	i = 0;
	while (cmd_tab[i])
	{
		if (ft_strcmp(cmd[0], cmd_tab[i]) == 0)
			state = TRUE;
		i++;
	}
	bn_freetab(cmd_tab);
	return (state);
}

// Upgrade error management
// 
int	execute_builtin(t_env **env, t_env **hidden, t_env **local, char **arg)//find cmd index, add local var
{
	int		code_error;
	char	*msg;

	code_error = 0;
	msg = 0;
	if (ft_strcmp(arg[0], "cd") == 0)
		bigerrno_cd(env, local, arg);
	else if (ft_strcmp(arg[0], "echo") == 0)
		bigerrno_echo(arg);
	else if (ft_strcmp(arg[0], "env") == 0)
		bigerrno_env(env, local, arg);
	else if (ft_strcmp(arg[0], "exit") == 0)
		bigerrno_exit(arg, &code_error, &msg);
	else if (ft_strcmp(arg[0], "export") == 0)
		bigerrno_export(env, hidden, local, arg);
	else if (ft_strcmp(arg[0], "pwd") == 0)
		bigerrno_pwd();
	else if (ft_strcmp(arg[0], "unset") == 0)
		bigerrno_unset(env, arg);
	else
		return (FALSE);
	free(msg);
	return (TRUE);
}

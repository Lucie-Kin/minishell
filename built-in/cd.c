/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:13:59 by lchauffo          #+#    #+#             */
/*   Updated: 2024/12/04 19:23:48 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	go_to_home(t_sh *sh, char **target_dir);
static int	go_to_oldpwd(t_sh *sh, char **target_dir);

int	bigerrno_cd(t_sh *sh, char **arg)
{
	int		code_err;
	char	*target_dir;

	code_err = 0;
	update_env(&sh->env, &sh->hidden);
	if (get_array_length((void **)arg) > 2)
		return (output_error(EPERM, compose_err_msg
				(SHELL, "cd", NULL, ERR_NB_ARGS)));
	if (!arg[1])
		code_err = go_to_home(sh, &target_dir);
	else if (ft_strcmp(arg[1], "-") == 0)
		code_err = go_to_oldpwd(sh, &target_dir);
	else
		target_dir = arg[1];
	if (!code_err && chdir(target_dir) != 0)
	{
		if (access(target_dir, F_OK) == 0)
			return (output_error(EPERM, compose_err_msg
					(SHELL, "cd", target_dir, strerror(EACCES))));
		return (output_error(EPERM, compose_err_msg
				(SHELL, "cd", target_dir, strerror(ENOENT))));
	}
	else if (arg[1] && target_dir && ft_strcmp(arg[1], "-") == 0)
		printf("%s\n", target_dir);
	return (update_pwd(sh, arg[1], code_err));
}

static int	go_to_home(t_sh *sh, char **target_dir)
{
	t_env	*home_var;

	home_var = find_key(&sh->local, "HOME");
	if (!home_var)
	{
		home_var = find_key(&sh->env, "HOME");
	}
	if (!home_var || !home_var->value)
	{
		output_error(EPERM, compose_err_msg(SHELL, "cd", NULL,
				"HOME not set"));
		return (EPERM);
	}
	*target_dir = home_var->value;
	return (0);
}

static int	go_to_oldpwd(t_sh *sh, char **target_dir)
{
	t_env	*oldpwd;

	*target_dir = NULL;
	oldpwd = find_key(&sh->local, "OLDPWD");
	if (!oldpwd)
		oldpwd = find_key(&sh->env, "OLDPWD");
	if (!oldpwd)
		oldpwd = find_key(&sh->hidden, "OLDPWD");
	if (!oldpwd || !oldpwd->value)
		return (output_error(EPERM, compose_err_msg(SHELL, "cd", NULL,
					"OLDPWD not set")));
	*target_dir = oldpwd->value;
	return (0);
}

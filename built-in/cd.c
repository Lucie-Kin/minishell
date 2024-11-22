/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:13:59 by lchauffo          #+#    #+#             */
/*   Updated: 2024/11/22 17:20:17 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_pwd(t_sh *sh)
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		return ;
	pwd = find_key(sh->env, "PWD");
	if (pwd)
	{
		oldpwd = find_key(sh->env, "OLDPWD");
		if (oldpwd)
		{
			if (oldpwd->value)
				free(oldpwd->value);
			oldpwd->value = ft_strdup(pwd->value);
			oldpwd->withvalue = TRUE;
		}
		if (pwd->value)
			free(pwd->value);
		pwd->value = current_dir;
		pwd->withvalue = TRUE;
	}
	else
		free(current_dir);
}

int	change_directory(char *path)
{
	if (ft_strcmp(path, "HOME") == 0)
	{
		output_error(EPERM,
			compose_err_msg(SHELL, "cd", NULL, "HOME not set"));
		return (EPERM);
	}
	if (ft_strcmp(path, "OLDPWD") == 0)
	{
		output_error(EPERM,
			compose_err_msg(SHELL, "cd", NULL, "OLDPWD not set"));
		return (EPERM);
	}
	if (chdir(path) != 0)
	{
		if (access(path, F_OK) == 0)
			output_error(EPERM,
				compose_err_msg(SHELL, "cd", path, strerror(EACCES)));
		else
			output_error(EPERM,
				compose_err_msg(SHELL, "cd", path, strerror(ENOENT)));
		return (EPERM);
	}
	return (0);
}

static int	go_to_home(t_sh *sh, char **target_dir)
{
	t_env	*home_var;

	home_var = find_key(sh->local, "HOME");
	if (home_var)
	{
		dprintf(2, "home_var in local found : %s = \"%s\"",
			home_var->key, home_var->value);
	}
	if (!home_var)
	{
		home_var = find_key(sh->env, "HOME");
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

	oldpwd = find_key(sh->local, "OLDPWD");
	if (!oldpwd)
		oldpwd = find_key(sh->env, "OLDPWD");
	if (!oldpwd || !oldpwd->value)
	{
		output_error(EPERM, compose_err_msg(SHELL, "cd", NULL,
				"OLDPWD not set"));
		return (EPERM);
	}
	printf("%s\n", oldpwd->value);
	*target_dir = oldpwd->value;
	return (0);
}

int	bigerrno_cd(t_sh *sh, char **arg)
{
	int		cod_err;
	char	*target_dir;

	cod_err = 0;
	// update_env(&sh->env, &sh->hidden);
	if (bn_linelen(arg) > 2)
		return (output_error(EPERM, compose_err_msg
				(SHELL, "cd", NULL, ERR_NB_ARGS)));
	if (!arg[1])
		cod_err = go_to_home(sh, &target_dir);
	else if (ft_strcmp(arg[1], "-") == 0)
		cod_err = go_to_oldpwd(sh, &target_dir);
	else
		target_dir = arg[1];
	if (!cod_err && chdir(target_dir) != 0)
	{
		if (access(target_dir, F_OK) == 0)
			cod_err = output_error(EPERM, compose_err_msg
					(SHELL, "cd", target_dir, strerror(EACCES)));
		else
			cod_err = output_error(EPERM, compose_err_msg
					(SHELL, "cd", target_dir, strerror(ENOENT)));
	}
	if (!cod_err)
		update_pwd(sh);
	return (cod_err);
}

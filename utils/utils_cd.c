/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:53:36 by lchauffo          #+#    #+#             */
/*   Updated: 2024/11/30 22:03:02 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_pwd(t_sh *sh)
{
	t_env	*pwd;
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		return ;
	pwd = find_key(&sh->env, "PWD");
	if (pwd)
	{
		update_oldpwd(sh, pwd);
		if (pwd->value)
			free(pwd->value);
		pwd->value = current_dir;
		pwd->withvalue = TRUE;
	}
	else
		free(current_dir);
}

void	update_oldpwd(t_sh *sh, t_env *pwd)
{
	t_env	*oldpwd;

	oldpwd = find_key(&sh->env, "OLDPWD");
	if (!oldpwd)
		oldpwd = find_key(&sh->hidden, "OLDPWD");
	if (oldpwd)
	{
		if (oldpwd->value)
			free(oldpwd->value);
		oldpwd->value = ft_strdup(pwd->value);
		oldpwd->withvalue = TRUE;
	}
	else
	{
		oldpwd = lst_new("OLDPWD", pwd->value);
		if (oldpwd)
			lstadd_back(&sh->hidden, oldpwd);
	}
}

int	go_to_home(t_sh *sh, char **target_dir)
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

int	go_to_oldpwd(t_sh *sh, char **target_dir)
{
	t_env	*oldpwd;

	oldpwd = find_key(&sh->local, "OLDPWD");
	if (!oldpwd)
		oldpwd = find_key(&sh->env, "OLDPWD");
	if (!oldpwd)
		oldpwd = find_key(&sh->hidden, "OLDPWD");
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

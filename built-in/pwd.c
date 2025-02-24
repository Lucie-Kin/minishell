/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:14:37 by lchauffo          #+#    #+#             */
/*   Updated: 2025/02/24 13:33:06 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigerrno.h"

static char	*get_cwd(t_sh *sh, const char *arg, int *code_err);
static void	update_oldpwd(t_sh *sh, t_env *pwd);

int	bigerrno_pwd(t_sh *sh)
{
	if (sh->pwd && sh->pwd->value)
		printf("%s\n", sh->pwd->value);
	return (0);
}

void	add_pwd(t_sh *sh)
{
	sh->pwd = ft_calloc(1, sizeof(t_sh));
	sh->pwd->value = getcwd(NULL, 0);
	sh->pwd->key = ft_strdup("PWD");
	sh->pwd->withvalue = TRUE;
	sh->pwd->prev = NULL;
	sh->pwd->next = NULL;
}

int	update_pwd(t_sh *sh, const char *arg, int code_err)
{
	char	*cwd;
	t_env	*var;

	if (code_err)
		return (code_err);
	cwd = get_cwd(sh, arg, &code_err);
	if (!cwd)
		return (code_err);
	free(sh->pwd->value);
	sh->pwd->value = cwd;
	var = find_key(&sh->env, "PWD");
	if (var)
	{
		update_oldpwd(sh, var);
		free(var->value);
		var->value = ft_strdup(sh->pwd->value);
		var->withvalue = TRUE;
	}
	return (code_err);
}

static char	*get_cwd(t_sh *sh, const char *arg, int *code_err)
{
	char	*cwd;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		tmp = ft_strjoin("getcwd: ", ERR_ACS_DIR);
		*code_err = output_error(EPERM, compose_err_msg("cd", ERR_CD, tmp,
					strerror(ENOENT)));
		free(tmp);
		tmp = ft_strjoin(sh->pwd->value, "/");
		cwd = ft_strjoin(tmp, arg);
		free(tmp);
	}
	return (cwd);
}

static void	update_oldpwd(t_sh *sh, t_env *pwd)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:13:59 by lchauffo          #+#    #+#             */
/*   Updated: 2024/12/03 13:57:09 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_paths_and_update(t_sh *sh, const char *arg, int code_err)
{
	char	*cwd;
	char	*tmp;

	if (code_err)
		return (code_err);
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		tmp = ft_strjoin("getcwd: ", ERR_ACS_DIR);
		code_err = output_error(EPERM, compose_err_msg("cd", ERR_CD, tmp,
					strerror(ENOENT)));
		free(tmp);
		tmp = ft_strjoin(sh->pwd->value, "/");
		cwd = ft_strjoin(tmp, arg);
		free(tmp);
	}
	update_pwd(sh, cwd);
	return (code_err);
}

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
	else if (ft_strcmp(arg[1], "-") == 0)
		printf("%s\n", target_dir);
	return (check_paths_and_update(sh, arg[1], code_err));
}

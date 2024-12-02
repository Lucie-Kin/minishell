/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:13:59 by lchauffo          #+#    #+#             */
/*   Updated: 2024/12/02 14:01:26 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_paths_and_update(t_sh *sh, int cod_err)
{
	char	*tmp;

	tmp = NULL;
	if (!cod_err)
	{
		tmp = getcwd(NULL, 0);
		if (tmp == NULL)
			cod_err = output_error(EPERM, compose_err_msg(NULL, "cd", \
			ft_strjoin(ft_strjoin(ft_strjoin(ERR_CD, ": "), ft_strjoin \
			("getcwd", ": ")), ERR_ACS_DIR), strerror(ENOENT)));
		update_pwd(sh);
	}
	free(tmp);
	return (cod_err);
}

int	bigerrno_cd(t_sh *sh, char **arg)
{
	int		cod_err;
	char	*target_dir;

	cod_err = 0;
	update_env(&sh->env, &sh->hidden);
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
	cod_err = check_paths_and_update(sh, cod_err);
	return (cod_err);
}

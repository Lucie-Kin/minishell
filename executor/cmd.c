/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:20:11 by libousse          #+#    #+#             */
/*   Updated: 2024/10/21 16:26:28 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// PATH >> verif si PATH=::, alors replace:: par getcwd, actual path
//if isbuiltin, execute builtin and ignore execve //!\\ 
static int	get_fullpath(t_pl *pl, char *cmd_name, char **cmd_fullpath);

int	resolve_command(t_pl *pl, char *cmd_name, char **cmd_fullpath)
{
	if (!cmd_name)//si la commande n'existe pas, fullpath est à NULL
		*cmd_fullpath = 0;
	else if (access(cmd_name, X_OK) >= 0)//le path est dans la cmd, cmd existe
		*cmd_fullpath = ft_strdup(cmd_name);//on passe telquel dans fullpath
	else//cmd pas vérifiable telquel et non-NULL
	{
		pl->exit_code = errno;//si ca échoue, retourne errno
		if (get_fullpath(pl, cmd_name, cmd_fullpath))//si PATH/cmd fonctionne
			pl->exit_code = 0;
		else if (pl->exit_code == ENOENT)//127-Not such file or directory
		{
			pl->exit_code = 127;
			pl->err_msg = compose_err_msg(cmd_name, 0, "command not found");
			return (0);
		}
		else
		{
			pl->err_msg = compose_err_msg(cmd_name, 0, strerror(pl->exit_code));
			return (0);
		}
	}
	return (1);
}

static int	join_fullpath(t_pl *pl, char *cmd_name, char *to_join, char **cmd_fullpath)
{
	char	*joined;

	joined = ft_strjoin(to_join, cmd_name);
	if (!joined)
	{
		pl->exit_code = ENOMEM;
		return (0);
	}
	if (access(joined, X_OK) >= 0)
	{
		*cmd_fullpath = joined;
		return (1);
	}
	free(joined);
}

static int	get_fullpath(t_pl *pl, char *cmd_name, char **cmd_fullpath)
{
	int		i;
	char	*cwd;

	if (!pl->path)
		return (0);
	i = 0;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		perror("Failed to find actual path");
	if (!pl->path || !pl->path[i])
		join_fullpath(pl, cmd_name, cwd, cmd_fullpath);
	while (pl->path[i])
	{
		join_fullpath(pl, cmd_name, pl->path[i], cmd_fullpath);
		++i;
	}
	free(cwd);
	return (0);
}

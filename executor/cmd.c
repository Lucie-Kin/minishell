/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:20:11 by libousse          #+#    #+#             */
/*   Updated: 2024/10/21 20:10:43 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//if isbuiltin, execute builtin and ignore execve !!!
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
		else if (pl->exit_code == ENOENT)//127-No such file or directory
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

/* `getcwd` is used in the parser if PATH var doesn't exist */
static int	get_fullpath(t_pl *pl, char *cmd_name, char **cmd_fullpath)
{
	size_t	i;
	char	*joined;

	if (!pl->path)
		return (0);
	i = 0;
	while (pl->path[i])
	{
		joined = ft_strjoin(pl->path[i], cmd_name);
		if (!joined)
		{
			pl->exit_code = ENOMEM;
			return (0);
		}
		else if (access(joined, X_OK) >= 0)
		{
			*cmd_fullpath = joined;
			return (1);
		}
		free(joined);
		++i;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:20:11 by libousse          #+#    #+#             */
/*   Updated: 2024/10/23 18:43:31 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_fullpath(t_pl *pl, char *cmd_name, char **cmd_fullpath);

int	resolve_command(t_pl *pl, char *cmd_name, char **cmd_fullpath)
{
	if (!cmd_name)
		*cmd_fullpath = 0;
	else if (access(cmd_name, X_OK) >= 0)
		*cmd_fullpath = ft_strdup(cmd_name);
	else
	{
		pl->exit_code = errno;
		if (get_fullpath(pl, cmd_name, cmd_fullpath))
			pl->exit_code = 0;
		else if (pl->exit_code == ENOENT)
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

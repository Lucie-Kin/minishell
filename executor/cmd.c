/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:20:11 by libousse          #+#    #+#             */
/*   Updated: 2024/11/16 17:56:52 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	search_cmd_on_path(t_pl *pl, char *cmd_name, char **cmd_fullpath);
static void	handle_not_found(t_pl *pl, char *cmd_name);
static int	is_not_directory(const char *path);
static int	is_directory(const char *path);

int	resolve_command(t_pl *pl, char *cmd_name, char **cmd_fullpath)
{
	if (!cmd_name)
		return (1);
	else if (access(cmd_name, X_OK) < 0)
	{
		if (pl->path && !ft_strchr(cmd_name, '/'))
			return (search_cmd_on_path(pl, cmd_name, cmd_fullpath));
		handle_not_found(pl, cmd_name);
		return (0);
	}
	else if (pl->path && !ft_strchr(cmd_name, '/'))
	{
		pl->exit_code = 127;
		pl->err_msg = compose_err_msg(0, cmd_name, 0, "command not found");
		return (0);
	}
	else if (is_directory(cmd_name))
	{
		pl->exit_code = 126;
		pl->err_msg = compose_err_msg(SHELL, cmd_name, 0, strerror(EISDIR));
		return (0);
	}
	*cmd_fullpath = ft_strdup(cmd_name);
	return (1);
}

static int	search_cmd_on_path(t_pl *pl, char *cmd_name, char **cmd_fullpath)
{
	size_t	i;
	char	*joined;

	i = 0;
	while (cmd_name[0] && pl->path && pl->path[i])
	{
		joined = ft_strjoin(pl->path[i], cmd_name);
		if (!joined)
			break ;
		else if (access(joined, X_OK) >= 0)
		{
			*cmd_fullpath = joined;
			return (1);
		}
		free(joined);
		++i;
	}
	pl->exit_code = 127;
	pl->err_msg = compose_err_msg(0, cmd_name, 0, "command not found");
	return (0);
}

static void	handle_not_found(t_pl *pl, char *cmd_name)
{
	if (access(cmd_name, F_OK) >= 0)
	{
		pl->exit_code = 126;
		pl->err_msg = compose_err_msg(SHELL, cmd_name, 0, strerror(EACCES));
	}
	else if (is_not_directory(cmd_name))
	{
		pl->exit_code = 126;
		pl->err_msg = compose_err_msg(SHELL, cmd_name, 0, strerror(ENOTDIR));
	}
	else
	{
		pl->exit_code = 127;
		pl->err_msg = compose_err_msg(SHELL, cmd_name, 0, strerror(ENOENT));
	}
	return ;
}

/* Has trailing forward slashes, exists, but is not a directory */
static int	is_not_directory(const char *path)
{
	int		exists;
	int		is_dir;
	char	*tmp;

	if (!path)
		return (0);
	tmp = ft_strchr(path, '/');
	if (!tmp)
		return (0);
	tmp = ft_substr(path, 0, tmp - path);
	if (!tmp)
		return (0);
	exists = access(tmp, F_OK) >= 0;
	is_dir = is_directory(tmp);
	free(tmp);
	return (exists && !is_dir);
}

static int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (!path || stat(path, &path_stat) < 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

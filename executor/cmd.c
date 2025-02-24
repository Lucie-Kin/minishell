/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:20:11 by libousse          #+#    #+#             */
/*   Updated: 2025/02/24 13:31:37 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigerrno.h"

static int	search_cmd_on_path(t_pl *pl, char *cmd_path, char **cmd_fullpath);
static int	is_executable(t_pl *pl, const char *cmd_path);
static int	is_directory(const char *cmd_path);
static int	is_not_directory(const char *cmd_path);

int	resolve_command(t_pl *pl, char *cmd_path, char **cmd_fullpath)
{
	if (!cmd_path)
		return (1);
	else if (pl->path && !ft_strchr(cmd_path, '/'))
		return (search_cmd_on_path(pl, cmd_path, cmd_fullpath));
	else if (is_executable(pl, cmd_path))
	{
		*cmd_fullpath = ft_strdup(cmd_path);
		return (1);
	}
	return (0);
}

static int	search_cmd_on_path(t_pl *pl, char *cmd_path, char **cmd_fullpath)
{
	size_t	i;
	char	*joined;

	i = 0;
	while (cmd_path[0] && pl->path && pl->path[i])
	{
		joined = ft_strjoin(pl->path[i], cmd_path);
		if (!joined)
			break ;
		else if (access(joined, X_OK) == 0)
		{
			*cmd_fullpath = joined;
			return (1);
		}
		free(joined);
		++i;
	}
	pl->exit_code = 127;
	pl->err_msg = compose_err_msg(0, cmd_path, 0, "command not found");
	return (0);
}

static int	is_executable(t_pl *pl, const char *cmd_path)
{
	if (is_directory(cmd_path))
	{
		pl->exit_code = 126;
		pl->err_msg = compose_err_msg(SHELL, cmd_path, 0, strerror(EISDIR));
		return (0);
	}
	else if (is_not_directory(cmd_path))
	{
		pl->exit_code = 126;
		pl->err_msg = compose_err_msg(SHELL, cmd_path, 0, strerror(ENOTDIR));
		return (0);
	}
	else if (access(cmd_path, F_OK) < 0)
	{
		pl->exit_code = 127;
		pl->err_msg = compose_err_msg(SHELL, cmd_path, 0, strerror(ENOENT));
		return (0);
	}
	else if (access(cmd_path, X_OK) < 0)
	{
		pl->exit_code = 126;
		pl->err_msg = compose_err_msg(SHELL, cmd_path, 0, strerror(EACCES));
		return (0);
	}
	return (1);
}

static int	is_directory(const char *cmd_path)
{
	struct stat	path_stat;

	if (!cmd_path || stat(cmd_path, &path_stat) < 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

/* Has trailing forward slashes in the input, exists, but is not a directory */
static int	is_not_directory(const char *cmd_path)
{
	int		exists;
	int		is_dir;
	char	*last_char;
	char	*name;

	if (!cmd_path)
		return (0);
	last_char = (char *)cmd_path + ft_strlen(cmd_path) - 1;
	if (*last_char != '/')
		return (0);
	while (*last_char == '/' && last_char > cmd_path)
		--last_char;
	if (*last_char == '/')
		return (0);
	name = ft_substr(cmd_path, 0, last_char - cmd_path + 1);
	if (!name)
		return (0);
	exists = access(name, F_OK) == 0;
	is_dir = is_directory(name);
	free(name);
	return (exists && !is_dir);
}

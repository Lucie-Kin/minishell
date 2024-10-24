/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:21:48 by libousse          #+#    #+#             */
/*   Updated: 2024/10/24 19:57:02 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static char	**get_split_path(t_sh *sh);
static char	**append_slash_to_path_strings(char **path);

char	**get_pl_path(t_sh *sh)
{
	return (append_slash_to_path_strings(get_split_path(sh)));
}

static char	**get_split_path(t_sh *sh)
{
	char	*var;
	char	**path;

	var = get_env(sh->env, "PATH");
	if (!var || !var[0])
		return (0);
	path = ft_split(var, ':');
	if (path && path[0])
		return (path);
	free(path);
	var = getcwd(NULL, 0);
	if (!var)
		return (0);
	path = ft_split(var, ':');
	free(var);
	return (path);
}

static char	**append_slash_to_path_strings(char **path)
{
	size_t	i;
	char	*tmp;

	if (!path)
		return (0);
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
		{
			free_entire_array((void **)path, free);
			return (0);
		}
		free(path[i]);
		path[i] = tmp;
		++i;
	}
	return (path);
}

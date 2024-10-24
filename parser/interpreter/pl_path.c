/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:21:48 by libousse          #+#    #+#             */
/*   Updated: 2024/10/23 01:13:09 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static char	**get_split_path(void);
static char	**append_slash_to_path_strings(char **path);

char	**get_pl_path(void)
{
	return (append_slash_to_path_strings(get_split_path()));
}

static char	**get_split_path(void)
{
	char	*var;
	char	**path;

	var = getenv("PATH");
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

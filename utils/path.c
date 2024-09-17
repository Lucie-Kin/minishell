/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:24:03 by libousse          #+#    #+#             */
/*   Updated: 2024/09/17 17:39:38 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_ending_slash(char **path);

char	**split_path(char **envp)
{
	char	**path;

	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH=", 5))
			break ;
		++envp;
	}
	if (!*envp)
		return (0);
	path = ft_split(*envp + 5, ':');
	if (!path)
		return (0);
	if (!add_ending_slash(path))
	{
		free_path(path);
		return (0);
	}
	return (path);
}

void	free_path(char **path)
{
	char	**ptr;

	if (!path)
		return ;
	ptr = path;
	while (*path)
	{
		free(*path);
		++path;
	}
	free(ptr);
	return ;
}

static int	add_ending_slash(char **path)
{
	size_t	i;
	size_t	len;
	char	*joined;

	i = 0;
	while (path[i])
	{
		len = ft_strlen(path[i]);
		if (len && path[i][len - 1] != '/')
		{
			joined = ft_strjoin(path[i], "/");
			if (!joined)
				return (0);
			free(path[i]);
			path[i] = joined;
		}
		++i;
	}
	return (1);
}

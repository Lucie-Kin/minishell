/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:21:48 by libousse          #+#    #+#             */
/*   Updated: 2024/10/19 18:26:57 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	**get_pl_path(void)
{
	size_t	i;
	char	**path;
	char	*tmp;

	path = ft_split(getenv("PATH"), ':');
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

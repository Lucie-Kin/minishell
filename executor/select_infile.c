/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_infile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:15:05 by libousse          #+#    #+#             */
/*   Updated: 2024/09/17 17:44:07 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_last_infile_fd(t_pl *pl, int catch_err)
{
	int	i;

	pl->fd_inf = -1;
	if (!pl->inf)
		return (1);
	i = 0;
	while (pl->inf[pl->index][i])
	{
		if (!check_file(pl, pl->inf[pl->index][i], R_OK, catch_err))
			return (0);
		else if (!pl->inf[pl->index][i + 1])
			pl->fd_inf = open(pl->inf[pl->index][i], O_RDONLY);
		++i;
	}
	return (1);
}

void	free_infiles(char ***files)
{
	int	i;
	int	j;

	if (!files)
		return ;
	i = 0;
	while (files[i])
	{
		j = 0;
		while (files[i][j])
		{
			free(files[i][j]);
			++j;
		}
		free(files[i]);
		++i;
	}
	free(files);
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_outfile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:15:50 by libousse          #+#    #+#             */
/*   Updated: 2024/09/17 17:44:44 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_last_outfile_fd(t_pl *pl, int catch_err)
{
	int	i;

	pl->fd_outf = -1;
	if (!pl->outf)
		return (1);
	i = 0;
	while (pl->outf[pl->index][i].filename)
	{
		if (!check_file(pl, pl->outf[pl->index][i].filename, W_OK,
			catch_err))
			return (0);
		pl->fd_outf = open(pl->outf[pl->index][i].filename,
				pl->outf[pl->index][i].flags, 0777);
		if (pl->outf[pl->index][i + 1].filename)
			close(pl->fd_outf);
		++i;
	}
	return (1);
}

void	free_outfiles(t_outf **files)
{
	int	i;
	int	j;

	if (!files)
		return ;
	i = 0;
	while (files[i])
	{
		j = 0;
		while (files[i][j].filename)
		{
			free(files[i][j].filename);
			++j;
		}
		free(files[i]);
		++i;
	}
	free(files);
	return ;
}

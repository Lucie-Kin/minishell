/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:05:42 by libousse          #+#    #+#             */
/*   Updated: 2024/09/17 17:43:04 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_last_heredoc_fd_and_free_unused_ones(t_pl *pl)
{
	int	i;
	int	j;

	pl->fd_hd = -1;
	if (!pl->hd)
		return ;
	i = 0;
	while (pl->hd[i])
	{
		j = 0;
		while (pl->hd[i][j] >= 0)
		{
			if (i == pl->index && pl->hd[i][j + 1] < 0)
				pl->fd_hd = pl->hd[i][j];
			else
				close(pl->hd[i][j]);
			++j;
		}
		free(pl->hd[i]);
		++i;
	}
	free(pl->hd);
	return ;
}

void	free_heredocs(int **heredocs)
{
	int	i;
	int	j;

	if (!heredocs)
		return ;
	i = 0;
	while (heredocs[i])
	{
		j = 0;
		while (heredocs[i][j] >= 0)
		{
			close(heredocs[i][j]);
			++j;
		}
		free(heredocs[i]);
		++i;
	}
	free(heredocs);
	return ;
}

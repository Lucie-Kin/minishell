/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_io_sources.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:43:49 by libousse          #+#    #+#             */
/*   Updated: 2024/09/17 17:44:36 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	In Bash 5, between a heredoc and an infile, the heredoc always has the 
	priority.

	In Bash 3, it's whichever was placed last for a given command. To make it 
	simple, there's a `favor_hd` boolean. It's set to 1 by default, and only 
	is it set to 0 when there was a heredoc but it wasn't last.
*/
void	set_input_source(t_pl *pl)
{
	if (pl->favor_hd[pl->index] && pl->fd_hd >= 0)
	{
		pl->fd_src[0] = pl->fd_hd;
		if (pl->fd_inf >= 0)
			close(pl->fd_inf);
		if (pl->index > 0)
			close(pl->fd_pipe[pl->index - 1][0]);
	}
	else if (pl->fd_inf >= 0)
	{
		pl->fd_src[0] = pl->fd_inf;
		if (pl->fd_hd >= 0)
			close(pl->fd_hd);
		if (pl->index > 0)
			close(pl->fd_pipe[pl->index - 1][0]);
	}
	else if (pl->index > 0)
		pl->fd_src[0] = pl->fd_pipe[pl->index - 1][0];
	else
		pl->fd_src[0] = -1;
	return ;
}

void	set_output_source(t_pl *pl)
{
	if (pl->fd_outf >= 0)
	{
		pl->fd_src[1] = pl->fd_outf;
		if (pl->index < pl->len - 1)
			close(pl->fd_pipe[pl->index][1]);
	}
	else if (pl->index < pl->len - 1)
		pl->fd_src[1] = pl->fd_pipe[pl->index][1];
	else
		pl->fd_src[1] = -1;
	return ;
}

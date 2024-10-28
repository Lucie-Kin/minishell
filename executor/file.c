/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:46:15 by libousse          #+#    #+#             */
/*   Updated: 2024/10/27 16:40:49 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_file(t_pl *pl, char *file, int mode, int catch_err);

int	set_last_infile_fd(t_pl *pl, int catch_err)
{
	int	i;

	pl->fd_src[0] = -1;
	if (!pl->inf || !pl->inf[pl->index])
		return (1);
	i = 0;
	while (pl->inf[pl->index][i])
	{
		if (!check_file(pl, pl->inf[pl->index][i], R_OK, catch_err))
			return (0);
		else if (!pl->inf[pl->index][i + 1])
			pl->fd_src[0] = open(pl->inf[pl->index][i], O_RDONLY);
		++i;
	}
	return (1);
}

int	set_last_outfile_fd(t_pl *pl, int catch_err)
{
	int	i;

	pl->fd_src[1] = -1;
	if (!pl->outf || !pl->outf[pl->index])
		return (1);
	i = 0;
	while (pl->outf[pl->index][i].filename)
	{
		if (!check_file(pl, pl->outf[pl->index][i].filename, W_OK,
			catch_err))
			return (0);
		pl->fd_src[1] = open(pl->outf[pl->index][i].filename,
				pl->outf[pl->index][i].flags, 0777);
		if (pl->outf[pl->index][i + 1].filename)
			close(pl->fd_src[1]);
		++i;
	}
	return (1);
}

static int	check_file(t_pl *pl, char *file, int mode, int catch_err)
{
	if (mode == W_OK && access(file, F_OK) < 0)
	{
		errno = 0;
		return (1);
	}
	else if (access(file, mode) < 0)
	{
		if (catch_err)
		{
			pl->exit_code = errno;
			pl->err_msg = compose_err_msg(SHELL_NAME, 0, file,
					strerror(pl->exit_code));
			if (pl->exit_code == EACCES)
				pl->exit_code = EPERM;
		}
		return (0);
	}
	return (1);
}

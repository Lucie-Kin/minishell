/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:46:15 by libousse          #+#    #+#             */
/*   Updated: 2025/02/24 13:33:06 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigerrno.h"

static int	open_infile(t_pl *pl, size_t i, int catch_err);
static int	open_outfile(t_pl *pl, size_t i, int catch_err);
static int	check_file(t_pl *pl, char *file, int mode, int catch_err);

int	set_fd_src_from_files(t_pl *pl, int catch_err)
{
	size_t	i;

	pl->fd_src[0] = -1;
	pl->fd_src[1] = -1;
	if (!pl->file || !pl->file[pl->index])
		return (1);
	i = 0;
	while (pl->file[pl->index][i].filename)
	{
		if (pl->file[pl->index][i].io == 0)
		{
			if (!open_infile(pl, i, catch_err))
				return (0);
		}
		else
		{
			if (!open_outfile(pl, i, catch_err))
				return (0);
		}
		++i;
	}
	return (1);
}

static int	open_infile(t_pl *pl, size_t i, int catch_err)
{
	if (pl->fd_src[0] >= 0)
		close(pl->fd_src[0]);
	if (!check_file(pl, pl->file[pl->index][i].filename, R_OK, catch_err))
	{
		pl->fd_src[0] = -1;
		return (0);
	}
	pl->fd_src[0] = open(pl->file[pl->index][i].filename,
			pl->file[pl->index][i].flags);
	return (1);
}

static int	open_outfile(t_pl *pl, size_t i, int catch_err)
{
	if (pl->fd_src[1] >= 0)
		close(pl->fd_src[1]);
	if (!check_file(pl, pl->file[pl->index][i].filename, W_OK, catch_err))
	{
		pl->fd_src[1] = -1;
		return (0);
	}
	errno = 0;
	pl->fd_src[1] = open(pl->file[pl->index][i].filename,
			pl->file[pl->index][i].flags, 0644);
	if (pl->fd_src[1] < 0)
	{
		pl->exit_code = errno;
		pl->err_msg = compose_err_msg(SHELL, 0, pl->file[pl->index][i].filename,
				strerror(pl->exit_code));
		if (pl->exit_code == EISDIR)
			pl->exit_code = EPERM;
		return (0);
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
			pl->err_msg = compose_err_msg(SHELL, 0, file,
					strerror(pl->exit_code));
			if (pl->exit_code == ENOENT || pl->exit_code == EACCES)
				pl->exit_code = EPERM;
		}
		return (0);
	}
	return (1);
}

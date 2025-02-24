/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:40:19 by libousse          #+#    #+#             */
/*   Updated: 2025/02/24 13:33:06 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigerrno.h"

static int	perform_redirections(t_pl *pl);
static int	redirect_src(t_pl *pl, int fd_dup[2], int io);

int	redirect_io(t_pl *pl)
{
	int	catch_err;

	catch_err = 1;
	pl->fd_std[0] = dup(STDIN_FILENO);
	pl->fd_std[1] = dup(STDOUT_FILENO);
	if (!set_fd_src_from_files(pl, catch_err))
		catch_err = 0;
	if (pl->fd_src[0] < 0 && pl->index > 0)
		pl->fd_src[0] = pl->fd_pipe[pl->index - 1][0];
	else if (pl->index > 0)
		close(pl->fd_pipe[pl->index - 1][0]);
	if (pl->fd_src[1] < 0 && pl->index == pl->len - 1 && pl->circular)
		pl->fd_src[1] = pl->fd_circ[1];
	else if (pl->fd_src[1] < 0 && pl->index < pl->len - 1)
		pl->fd_src[1] = pl->fd_pipe[pl->index][1];
	else if (pl->index < pl->len - 1)
		close(pl->fd_pipe[pl->index][1]);
	if (!catch_err)
		return (0);
	if (!perform_redirections(pl))
		return (0);
	return (1);
}

int	restore_io(t_pl *pl)
{
	char	buffer[1024];

	if (!isatty(STDIN_FILENO))
	{
		while (read(STDIN_FILENO, buffer, 1024 - 1) > 0)
			;
	}
	if (pl->fd_src[0] >= 0)
		close(pl->fd_src[0]);
	if (pl->fd_src[1] >= 0)
		close(pl->fd_src[1]);
	if (pl->circular)
	{
		close(pl->fd_circ[0]);
		close(pl->fd_circ[1]);
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	dup2(pl->fd_std[0], STDIN_FILENO);
	close(pl->fd_std[0]);
	dup2(pl->fd_std[1], STDOUT_FILENO);
	close(pl->fd_std[1]);
	output_error(pl->exit_code, pl->err_msg);
	return (pl->exit_code);
}

static int	perform_redirections(t_pl *pl)
{
	int	fd_dup[2];
	int	err_codes[2];

	err_codes[0] = redirect_src(pl, fd_dup, 0);
	err_codes[1] = redirect_src(pl, fd_dup, 1);
	if (!err_codes[0] && !err_codes[1])
		return (1);
	else if (err_codes[0])
		pl->exit_code = err_codes[0];
	else if (err_codes[1])
		pl->exit_code = err_codes[1];
	close(fd_dup[0]);
	close(fd_dup[1]);
	return (0);
}

static int	redirect_src(t_pl *pl, int fd_dup[2], int io)
{
	int	code;
	int	new_fd;

	code = 0;
	if (pl->fd_src[io] > 0)
	{
		new_fd = STDIN_FILENO;
		if (io == 1)
			new_fd = STDOUT_FILENO;
		fd_dup[io] = dup2(pl->fd_src[io], new_fd);
		if (fd_dup[io] < 0)
			code = errno;
		close(pl->fd_src[io]);
		pl->fd_src[io] = -1;
	}
	return (code);
}

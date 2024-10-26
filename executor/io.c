/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:46:15 by libousse          #+#    #+#             */
/*   Updated: 2024/10/26 16:35:54 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_file(t_pl *pl, char *file, int mode, int catch_err);
static int	redirect_src(t_pl *pl, int fd_dup[2], int io);

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
		{
			pl->fd_src[0] = open(pl->inf[pl->index][i], O_RDONLY);
			if (pl->fd_src[0] < 0)
				return (0);
		}
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
				pl->outf[pl->index][i].flags, 0644);
		if (pl->fd_src[1] < 0)
		{
			pl->exit_code = errno;
			pl->err_msg = compose_err_msg(SHELL_NAME,
					pl->outf[pl->index][i].filename, strerror(pl->exit_code));
			printf("Error opening file %s: %s\n",
				pl->outf[pl->index][i].filename, strerror(pl->exit_code));
			return (0);
		}
		if (pl->outf[pl->index][i + 1].filename)
			close(pl->fd_src[1]);
		++i;
	}
	return (1);
}

int	redirect_cmd_io(t_pl *pl)
{
	int	fd_dup[2];
	int	err_codes[2];

	fd_dup[0] = -1;
	fd_dup[1] = -1;
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

// Modification pour essayer de réparer "> out" dans le terminal
static int	check_file(t_pl *pl, char *file, int mode, int catch_err)
{
	if (mode == W_OK && access(file, F_OK) < 0)
	{
		pl->exit_code = ENOENT;
		pl->err_msg = compose_err_msg(SHELL_NAME, file, strerror(pl->exit_code));
		// errno = 0;
		return (0);
	}
	else if (access(file, mode) < 0)
	{
		if (catch_err)
		{
			pl->exit_code = errno;
			pl->err_msg = compose_err_msg(SHELL_NAME, file,
					strerror(pl->exit_code));
			if (pl->exit_code == EACCES)
				pl->exit_code = EPERM;
		}
		return (0);
	}
	return (1);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:46:15 by libousse          #+#    #+#             */
/*   Updated: 2024/09/17 17:46:36 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_input(t_pl *pl, int fd_dup[2]);
static int	redirect_output(t_pl *pl, int fd_dup[2]);

int	redirect_cmd_io(t_pl *pl)
{
	int	fd_dup[2];
	int	err_codes[2];

	err_codes[0] = redirect_input(pl, fd_dup);
	err_codes[1] = redirect_output(pl, fd_dup);
	if (err_codes[0])
		pl->exit_code = err_codes[0];
	else if (err_codes[1])
		pl->exit_code = err_codes[1];
	else
		return (1);
	close(fd_dup[0]);
	close(fd_dup[1]);
	return (!err_codes[0] && !err_codes[1]);
}

static int	redirect_input(t_pl *pl, int fd_dup[2])
{
	int	code;

	code = 0;
	if (pl->fd_src[0] > 0)
	{
		fd_dup[0] = dup2(pl->fd_src[0], STDIN_FILENO);
		if (fd_dup[0] < 0)
			code = errno;
		close(pl->fd_src[0]);
		pl->fd_src[0] = -1;
	}
	return (code);
}

static int	redirect_output(t_pl *pl, int fd_dup[2])
{
	int	code;

	code = 0;
	if (pl->fd_src[1] > 0)
	{
		fd_dup[1] = dup2(pl->fd_src[1], STDOUT_FILENO);
		if (fd_dup[1] < 0)
			code = errno;
		close(pl->fd_src[1]);
		pl->fd_src[1] = -1;
	}
	return (code);
}

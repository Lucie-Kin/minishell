/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subprocess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:26:09 by libousse          #+#    #+#             */
/*   Updated: 2024/10/26 20:08:47 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_redirections(t_pl *pl);
static int	close_file_descriptors(t_pl *pl, int std);

int	execute_subprocess(t_pl *pl, t_sh *sh)
{
	char	*cmd_fullpath;

	cmd_fullpath = 0;
	close_unused_pipes(pl->index, pl->fd_pipe, pl->fd_pipe_len);
	if (!handle_redirections(pl))
		return (close_file_descriptors(pl, 1));
	if (execute_builtin(&sh->env, &sh->hidden, &sh->local,
			sh->ex->pl.cmdl[pl->index]))
		return (close_file_descriptors(pl, 1));
	if (!resolve_command(pl, pl->cmdl[pl->index][0], &cmd_fullpath))
		return (close_file_descriptors(pl, 1));
	close_file_descriptors(pl, 0);
	if (cmd_fullpath)
	{
		if (ft_strcmp(cmd_fullpath, "./minishell") == 0)
			update_shlvl(&sh->env, FALSE);
		execve(cmd_fullpath, pl->cmdl[pl->index], convert_to_tab(sh->env));
		pl->exit_code = errno;
		pl->err_msg = compose_err_msg(pl->cmdl[pl->index][0], 0,
				strerror(pl->exit_code));
		free(cmd_fullpath);
	}
	close(STDIN_FILENO);
	return (pl->exit_code);
}

static int	handle_redirections(t_pl *pl)
{
	int	catch_err;

	catch_err = 1;
	if (!set_last_infile_fd(pl, catch_err))
		catch_err = 0;
	if (!set_last_outfile_fd(pl, catch_err))
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
	if (!redirect_cmd_io(pl))
		return (0);
	return (1);
}

static int	close_file_descriptors(t_pl *pl, int std)
{
	if (pl->fd_src[0] >= 0)
		close(pl->fd_src[0]);
	if (pl->fd_src[1] >= 0)
		close(pl->fd_src[1]);
	if (pl->circular)
	{
		close(pl->fd_circ[0]);
		close(pl->fd_circ[1]);
	}
	if (std)
		close(STDIN_FILENO);
	return (pl->exit_code);
}

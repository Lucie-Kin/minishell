/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subprocess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:26:09 by libousse          #+#    #+#             */
/*   Updated: 2024/09/17 17:38:43 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_redirections(t_pl *pl);
static int	free_pipeline_resources_in_child(t_pl *pl);

void	execute_subprocess(t_pl *pl)
{
	char	*cmd_fullpath;

	close_unused_pipes(pl->index, pl->fd_pipe, pl->fd_pipe_len);
	if (!handle_redirections(pl))
		exit(free_pipeline_resources_in_child(pl));
	if (!resolve_command(pl, pl->cmdl[pl->index][0], &cmd_fullpath))
		exit(free_pipeline_resources_in_child(pl));
	free_pipeline_resources_in_child(pl);
	if (cmd_fullpath)
	{
		execve(cmd_fullpath, pl->cmdl[pl->index], pl->envp);
		pl->exit_code = errno;
		pl->err_msg = compose_err_msg(pl->cmdl[pl->index][0], 0,
				strerror(pl->exit_code));
		output_error(pl);
	}
	free(cmd_fullpath);
	free_cmdl(pl->cmdl);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(pl->exit_code);
	return ;
}

static int	handle_redirections(t_pl *pl)
{
	int	catch_err;

	catch_err = 1;
	set_last_heredoc_fd_and_free_unused_ones(pl);
	if (!set_last_infile_fd(pl, catch_err))
		catch_err = 0;
	free_infiles(pl->inf);
	if (!set_last_outfile_fd(pl, catch_err))
		catch_err = 0;
	free_outfiles(pl->outf);
	set_input_source(pl);
	set_output_source(pl);
	if (!catch_err)
		return (0);
	if (!redirect_cmd_io(pl))
		return (0);
	return (1);
}

static int	free_pipeline_resources_in_child(t_pl *pl)
{
	free_path(pl->path);
	pl->path = 0;
	if (pl->exit_code)
	{
		free_cmdl(pl->cmdl);
		pl->cmdl = 0;
		free(pl->favor_hd);
		pl->favor_hd = 0;
	}
	if (pl->fd_src[0] >= 0)
	{
		close(pl->fd_src[0]);
		pl->fd_src[0] = -1;
	}
	if (pl->fd_src[1] >= 0)
	{
		close(pl->fd_src[1]);
		pl->fd_src[1] = -1;
	}
	free_pipes(pl->fd_pipe);
	pl->fd_pipe = 0;
	return (output_error(pl));
}

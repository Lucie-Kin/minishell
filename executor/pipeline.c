/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:49:18 by libousse          #+#    #+#             */
/*   Updated: 2024/11/13 15:16:17 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	free_pipeline_resources(t_pl *pl);
static void	fork_subprocesses(t_sh *sh, int *pid);
static int	execute_subprocess(t_sh *sh, t_pl *pl);

int	execute_pipeline(t_sh *sh)
{
	int	*pid;

	sh->ex->pl.fd_pipe = open_pipes(&sh->ex->pl);
	if (!sh->ex->pl.fd_pipe)
		return (free_pipeline_resources(&sh->ex->pl));
	pid = ft_calloc(sh->ex->pl.len + 1, sizeof(int));
	if (!pid)
	{
		sh->ex->pl.exit_code = ENOMEM;
		return (free_pipeline_resources(&sh->ex->pl));
	}
	fork_subprocesses(sh, pid);
	free_pipeline_resources(&sh->ex->pl);
	wait_for_subprocesses(sh, pid);
	free(pid);
	return (sh->ex->pl.exit_code);
}

static int	free_pipeline_resources(t_pl *pl)
{
	close_pipes(pl->fd_pipe, pl->fd_pipe_len);
	if (pl->circular)
		close(pl->fd_circ[1]);
	output_error(pl->exit_code, pl->err_msg);
	pl->err_msg = 0;
	return (pl->exit_code);
}

static void	fork_subprocesses(t_sh *sh, int *pid)
{
	int	child_exit_code;

	while (sh->ex->pl.index < sh->ex->pl.len)
	{
		pid[sh->ex->pl.index] = fork();
		if (pid[sh->ex->pl.index] < 0)
		{
			sh->ex->pl.exit_code = errno;
			sh->ex->pl.err_msg = compose_err_msg(0, "fork", 0,
					strerror(sh->ex->pl.exit_code));
			break ;
		}
		else if (!pid[sh->ex->pl.index])
		{
			++sh->subshell;
			update_shlvl(&sh->env, TRUE);
			free(pid);
			child_exit_code = execute_subprocess(sh, &sh->ex->pl);
			destroy_all_ex(sh);
			free_shell(sh);
			exit(child_exit_code);
		}
		++sh->ex->pl.index;
	}
	return ;
}

static int	execute_subprocess(t_sh *sh, t_pl *pl)
{
	char	*cmd_fullpath;

	cmd_fullpath = 0;
	close_unused_pipes(pl->index, pl->fd_pipe, pl->fd_pipe_len);
	if (!redirect_io(pl))
		return (restore_io(pl));
	if (isbuiltin(pl->cmdl[pl->index], sh->local))
	{
		sh->exit_code = execute_builtin(sh);
		return (restore_io(pl));
	}
	if (!resolve_command(pl, pl->cmdl[pl->index][0], &cmd_fullpath))
		return (restore_io(pl));
	if (cmd_fullpath)
	{
		if (is_shell(sh->shells, cmd_fullpath))
			update_shlvl(&sh->env, FALSE);
		set_signals(1);
		execve(cmd_fullpath, pl->cmdl[pl->index], convert_to_tab(sh->env));
		pl->exit_code = errno;
		pl->err_msg = compose_err_msg(0, pl->cmdl[pl->index][0], 0,
				strerror(pl->exit_code));
		free(cmd_fullpath);
	}
	return (restore_io(pl));
}

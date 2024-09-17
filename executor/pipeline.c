/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:49:18 by libousse          #+#    #+#             */
/*   Updated: 2024/09/17 17:33:58 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fork_subprocesses(t_pl *pl, int *pid);
static int	wait_for_subprocesses(t_pl *pl, int *pid, int catch_err);

int	execute_pipeline(t_pl *pl)
{
	int	*pid;
	int	last_subprocess_exit_code;

	pl->fd_pipe = open_pipes(pl);
	if (!pl->fd_pipe)
		return (free_pipeline_resources_in_parent(pl));
	pid = ft_calloc(pl->len + 1, sizeof(int));
	if (!pid)
	{
		pl->exit_code = ENOMEM;
		return (free_pipeline_resources_in_parent(pl));
	}
	if (!fork_subprocesses(pl, pid))
		return (pl->exit_code);
	free_pipeline_resources_in_parent(pl);
	last_subprocess_exit_code = wait_for_subprocesses(pl, pid, 1);
	free(pid);
	return (last_subprocess_exit_code);
}

int	free_pipeline_resources_in_parent(t_pl *pl)
{
	pl->index = -1;
	free_path(pl->path);
	free_cmdl(pl->cmdl);
	close_pipes(pl->fd_pipe, pl->fd_pipe_len);
	free_pipes(pl->fd_pipe);
	free(pl->favor_hd);
	free_heredocs(pl->hd);
	free_infiles(pl->inf);
	free_outfiles(pl->outf);
	return (output_error(pl));
}

static int	fork_subprocesses(t_pl *pl, int *pid)
{
	while (++pl->index < pl->len)
	{
		pid[pl->index] = fork();
		if (pid[pl->index] < 0)
		{
			pl->exit_code = errno;
			pl->err_msg = compose_err_msg("fork", 0, strerror(pl->exit_code));
			free_pipeline_resources_in_parent(pl);
			wait_for_subprocesses(pl, pid, 0);
			free(pid);
			return (0);
		}
		else if (!pid[pl->index])
		{
			free(pid);
			execute_subprocess(pl);
		}
	}
	return (1);
}

/*
	The subprocess either exited normally (`exit` or returning from `main`) or 
	due to a signal. Exit codes are in a [0-255] range, with the [0-127] range 
	meant for normal exits, and the [128-255] range for signaled exits. Only a 
	normal exit provides an exit code, which is why 128 is added to a signal 
	number to create the exit code.

	The macros in `wait_for_subprocesses` are part of `waitpid` and are not 
	extra functions.
*/
static int	wait_for_subprocesses(t_pl *pl, int *pid, int catch_err)
{
	int	i;
	int	status;
	int	signal_number;

	i = 0;
	while (pid[i])
	{
		if (waitpid(pid[i], &status, 0) < 0 && catch_err)
		{
			pl->exit_code = errno;
			pl->err_msg = compose_err_msg("waitpid", 0,
					strerror(pl->exit_code));
			output_error(pl);
		}
		else if (WIFEXITED(status))
			pl->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			signal_number = WTERMSIG(status);
			pl->exit_code = 128 + signal_number;
		}
		++i;
	}
	return (pl->exit_code);
}

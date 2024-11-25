/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:49:18 by libousse          #+#    #+#             */
/*   Updated: 2024/11/24 14:39:50 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	free_pipeline_resources(t_pl *pl);
static void	fork_subprocesses(t_sh *sh, int *pid);

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:35:57 by libousse          #+#    #+#             */
/*   Updated: 2024/09/17 17:36:35 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	**allocate_pipes(int pipe_len);

/* Number of pipes = `cmd amount - 1` */
int	**open_pipes(t_pl *pl)
{
	int	i;
	int	**pipes;

	pipes = allocate_pipes(pl->fd_pipe_len);
	if (!pipes)
	{
		pl->exit_code = ENOMEM;
		return (0);
	}
	i = 0;
	while (i < pl->fd_pipe_len)
	{
		if (pipe(pipes[i]) < 0)
		{
			pl->exit_code = errno;
			pl->err_msg = compose_err_msg(0, "pipe", 0, strerror(pl->exit_code));
			close_pipes(pipes, i);
			free_entire_array((void **)pipes, free);
			return (0);
		}
		++i;
	}
	return (pipes);
}

void	close_pipes(int **pipes, int len)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < len)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		++i;
	}
	return ;
}

/*
	A process writes to `pipe[index][1]` and reads from `pipe[index - 1][0]`.
	Special cases:
		- If `index == 0`, the process doesn't read from a pipe.
		- If `index == pipe_len`, the process doesn't write to a pipe.
*/
void	close_unused_pipes(int index, int **pipes, int pipe_len)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < pipe_len)
	{
		if (i == index)
			close(pipes[i][0]);
		else if (i == (index - 1))
			close(pipes[i][1]);
		else
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
		}
		++i;
	}
	return ;
}

static int	**allocate_pipes(int pipe_len)
{
	int	i;
	int	**pipes;

	pipes = ft_calloc(pipe_len + 1, sizeof(int *));
	if (!pipes)
		return (0);
	i = 0;
	while (i < pipe_len)
	{
		pipes[i] = malloc(2 * sizeof(int));
		if (!pipes[i])
		{
			free_entire_array((void **)pipes, free);
			return (0);
		}
		++i;
	}
	return (pipes);
}

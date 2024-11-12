/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:21:04 by libousse          #+#    #+#             */
/*   Updated: 2024/11/11 19:44:24 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_status_of_last_child(int *pid);

/*
	The subprocess either exited normally (`exit` or returning from `main`) or 
	due to a signal. Exit codes are in a [0-255] range, with the [0-127] range 
	meant for normal exits, and the [128-255] range for signaled exits. Only a 
	normal exit provides an exit code, which is why 128 is added to a signal 
	number to create the exit code.

	The macros in `wait_for_subprocesses` are part of `waitpid` and are not 
	extra functions.

	About the core dump, it should be generated on SIGQUIT, but I'm not certain 
	it happens and print the flavor text anyway.
*/
void	wait_for_subprocesses(t_sh *sh, int *pid)
{
	int	status;
	int	signal_number;

	set_signal_handling(SIGINT, update_sig_var);
	status = get_status_of_last_child(pid);
	set_signal_handling(SIGINT, signal_handler);
	if (sh->ex->pl.exit_code || !status)
		return ;
	else if (WIFEXITED(status))
		sh->ex->pl.exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		signal_number = WTERMSIG(status);
		sh->ex->pl.exit_code = 128 + signal_number;
		if (signal_number == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)", 2);
		ft_putstr_fd("\n", 2);
	}
	return ;
}

static int	get_status_of_last_child(int *pid)
{
	size_t	i;
	int		err;
	int		status;

	i = 0;
	status = 0;
	while (pid[i])
	{
		err = waitpid(pid[i], &status, 0);
		while (err < 0)
		{
			if (errno == EINTR && g_signum == SIGINT)
			{
				g_signum = 0;
				err = waitpid(pid[i], &status, 0);
			}
			else
				break ;
		}
		++i;
	}
	return (status);
}

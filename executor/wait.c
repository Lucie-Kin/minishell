/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:21:04 by libousse          #+#    #+#             */
/*   Updated: 2025/02/24 13:33:06 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigerrno.h"

static int	get_status_of_last_child(int *pid, int options);

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
void	wait_for_subprocesses(t_sh *sh, int *pid, int options)
{
	int	status;
	int	signal_number;

	set_signal_handling(SIGINT, SIG_IGN);
	status = get_status_of_last_child(pid, options);
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
			ft_putstr_fd("Quit (core dumped)", STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	return ;
}

static int	get_status_of_last_child(int *pid, int options)
{
	size_t	i;
	int		err;
	int		status;

	i = 0;
	status = 0;
	while (pid[i])
	{
		err = waitpid(pid[i], &status, options);
		while (err < 0 && errno == EINTR)
			err = waitpid(pid[i], &status, 0);
		++i;
	}
	return (status);
}

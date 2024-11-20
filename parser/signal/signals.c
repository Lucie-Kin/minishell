/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 15:46:13 by libousse          #+#    #+#             */
/*   Updated: 2024/11/16 17:52:08 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Ctrl-\ (SIGQUIT) is ignored in the shell, but it makes an external process 
	terminate and generates a core dump for it.

	Ctrl-C (SIGINT) cancels the current input line when in the shell. It makes 
	an external process terminate.

	Ctrl-D is not a signal. It sends the EOT character, which expresses EOF to 
	STDIN. It makes the readline function return NULL.
*/

int	set_signals(int reset)
{
	if (reset)
		return (set_signal_handling(SIGQUIT, SIG_DFL)
			&& set_signal_handling(SIGINT, SIG_DFL));
	return (set_signal_handling(SIGQUIT, SIG_IGN)
		&& set_signal_handling(SIGINT, signal_handler));
}

int	set_signal_handling(int signum, void (*handler)(int))
{
	struct sigaction	sa;
	char				*str_sig;

	sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(signum, &sa, 0) < 0)
	{
		str_sig = ft_itoa(signum);
		output_error(errno, compose_err_msg(SHELL, "sigaction", str_sig,
				strerror(errno)));
		free(str_sig);
		return (0);
	}
	return (1);
}

void	signal_handler(int signum)
{
	g_signum = signum;
	if (signum == SIGINT)
		close(STDIN_FILENO);
	return ;
}

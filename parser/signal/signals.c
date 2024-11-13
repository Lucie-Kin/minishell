/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 15:46:13 by libousse          #+#    #+#             */
/*   Updated: 2024/11/13 13:51:57 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Ctrl-\ (SIGQUIT) must be blocked in the shell, and still needs to quit and 
	generate a core dump in external processes. Simply revert it to its default 
	behavior before calling execve. The core dump message doesn't show, so add 
	it yourself.

	Ctrl-C (SIGINT) in a shell is meant to cancel the current input line. Its 
	default behavior is to terminate the program, which is replaced with the 
	behavior of updating a global variable with the signal value. In an 
	external process, it's meant to terminate it.

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

void	update_sig_var(int signum)
{
	if (g_signum > 0 && signum == EOF)
		g_signum = -g_signum;
	else
		g_signum = signum;
	return ;
}

void	signal_handler(int signum)
{
	update_sig_var(signum);
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return ;
}

/*
	SIGINT ISSUE
	Instead of printing a hardcoded prompt, make the main struct a global var 
	and call `rl_set_prompt` before `rl_redisplay` with the proper prompt.
*/
void	signal_handler_extra(int signum)
{
	update_sig_var(signum);
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		ft_putstr_fd("\001\e[1;32m\002user@host\001\e[0m\002:"
			"\001\e[1;34m\002path\001\e[0m\002$ ", 1);
		rl_replace_line("", 0);
	}
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:14:05 by libousse          #+#    #+#             */
/*   Updated: 2024/10/23 15:52:21 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_sh	sh;

	if (argc > 1)
		return (output_error(1,
				compose_err_msg(SHELL_NAME, 0, "Too many arguments")));
	/*
		- Duplicate the environment and use your own `getenv` function.
		- On exit, free the hidden var list, not just the environment.
		- As for Valgrind flags, check for unclosed FDs with `--track-fds=yes`, 
		and you can add `--trace-children=yes` to find out in which child 
		process you need to close them.

		- You can increment the SHLVL variable when executing a new bigerrno 
		(and not when forking for a subshell), as every shell increments it. 
		And if this var didn't exist, add it and set it to 1. The t_sh `level` 
		variable is different and is there to tell whether "exit" should be 
		printed. It's the one you increment when forking for a subshell.
	*/
	ft_bzero(&sh, sizeof(t_sh));
	sh.first_arg = argv[0];
	sh.pid = ft_itoa(get_pid(&sh, sh.first_arg));
	sh.user = get_username(&sh);
	sh.host = get_hostname(&sh);
	sh.home = get_home_path(&sh, sh.user);
	sh.envp = envp;//use convert_list.c
	run_shell(&sh);
	free_shell(&sh);
	if (sh.level == 0)
		ft_putstr_fd("exit\n", 1);
	return (sh.exit_code);
}

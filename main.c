/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:14:05 by libousse          #+#    #+#             */
/*   Updated: 2024/10/13 12:00:31 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_sh	sh;

	if (argc > 1)
		return (output_error_UPDATE(1,
				compose_err_msg(SHELL_NAME, 0, "Too many arguments")));
	if (!envp[0])
		return (output_error_UPDATE(1,
				compose_err_msg(SHELL_NAME, 0, "No environment variable")));
	/*
		- Duplicate the environment.
		- Don't use `getenv`, rewrite the function and search your env copy.
		- Set your $PWD on shell startup, don't trust its original value (also, 
		the var may not even exist to begin with).
		- You can increment the SHLVL variable when executing a new bigerrno 
		(and not when forking for a subshell), as every shell increments it. 
		And if this var didn't exist, add it and set it to 1. The t_sh `level` 
		variable is different and is there to tell whether "exit" should be 
		printed. It's the one you increment when forking for a subshell.
	*/
	sh.first_arg = argv[0];
	sh.pid = ft_itoa(get_pid(sh.first_arg));
	sh.level = 0;
	sh.envp = envp;
	run_shell(&sh);
	free_shell(&sh);
	/* When forking a subshell, increment `level` within said subshell. */
	if (sh.level == 0)
		ft_putstr_fd("exit\n", 1);
	return (sh.exit_code);
}

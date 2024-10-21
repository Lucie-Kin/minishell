/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:14:05 by libousse          #+#    #+#             */
/*   Updated: 2024/10/21 15:42:39 by lchauffo         ###   ########.fr       */
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
		- Try to allow the env to be empty, instead of returning an error. For 
		the prompt, `whoami` to get the username, and `uname -n` to get the 
		hostname. Don't even care about whether the PATH var exists or not, 
		search in /bin. If you don't find them because the system is not like 
		other girls, just write "user" and "host" in the prompt.
		- Free the hidden var list, not just the environment (export/env).
		- Should the PATH be split in the command subprocess, or in the 
		pipeline subprocess? For now it's at pipeline level.
	*/
	ft_bzero(&sh, sizeof(t_sh));
	sh.first_arg = argv[0];
	sh.pid = ft_itoa(get_pid(sh.first_arg));//bonus replace cmd getpid
	sh.envp = envp;//use convert_list.c
	run_shell(&sh);//increase SHLVL in env
	free_shell(&sh);
	/* When forking a subshell, increment `level` within said subshell. */
	if (sh.level == 0)
		ft_putstr_fd("exit\n", 1);
	return (sh.exit_code);
}

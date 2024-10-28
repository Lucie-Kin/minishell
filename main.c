/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:14:05 by libousse          #+#    #+#             */
/*   Updated: 2024/10/28 16:15:11 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_sh	sh;

	if (argc > 1)
		return (output_error(1,
				compose_err_msg(SHELL_NAME, 0, 0, "Too many arguments")));
	/*
		- You can increment the SHLVL variable when executing a new bigerrno 
		(and not when forking for a subshell), as every shell increments it. 
		And if this var didn't exist, add it and set it to 1. The t_sh `level` 
		variable is different and is there to tell whether "exit" should be 
		printed. It's the one you increment when forking for a subshell.

		- As for Valgrind flags, check for unclosed FDs with `--track-fds=yes`, 
		and you can add `--trace-children=yes` to find out in which child 
		process you need to close them.

		- Get current background color with `echo -e "\033]11;?\007"`. It'd be 
		used when exiting the main function, to restore the original color. If 
		it's too tricky, just hardcode the grey color we have at school.
	*/
	set_background_color_to_gnome_purple();
	ft_bzero(&sh, sizeof(t_sh));
	sh.first_arg = argv[0];
	sh.env = convert_to_list(envp);
	update_shlvl(&sh.env, FALSE);
	sh.pid = ft_itoa(get_pid(&sh, sh.first_arg));
	sh.user = get_username(&sh);
	sh.host = get_hostname(&sh);
	sh.home = get_home_path(&sh, sh.user);
	run_shell(&sh);
	free_shell(&sh);
	if (sh.level == 0)
	{
		close(STDIN_FILENO);
		readline("\001\e]0;Terminal\a\002");
		ft_putstr_fd("exit\n", 1);
		set_background_color("11;rgb:2e2e/3434/3636");
	}
	return (sh.exit_code);
}

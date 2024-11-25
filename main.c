/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:14:05 by lchauffo          #+#    #+#             */
/*   Updated: 2024/11/25 17:49:38 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signum;

int	main(int argc, char **argv, char **envp)
{
	/*
		cat > out1 < missing > out2
		-> files need to be checked in order, not infiles and then outfiles
	*/
	t_sh	sh;

	handle_no_tty();
	if (argc > 1)
		return (output_error(1,
				compose_err_msg(SHELL, 0, 0, "Too many arguments")));
	if (!set_signals(0))
		return (1);
	ft_bzero(&sh, sizeof(t_sh));
	handle_default_background_color(0);
	set_background_color_to_gnome_purple();
	sh.first_arg = argv[0];
	sh.pid = ft_itoa(get_pid(&sh, sh.first_arg));
	sh.user = circular_pipeline(&sh, "/bin/whoami");
	sh.host = circular_pipeline(&sh, "/bin/uname -n | /bin/cut -d. -f1");
	sh.home = get_home_path(&sh, sh.user);
	sh.shells = get_shells(&sh);
	sh.env = convert_to_list(envp);
	add_pwd(&sh);
	update_shlvl(&sh.env, FALSE);
	run_shell(&sh);
	free_shell(&sh);
	if (sh.subshell == 0)
		reset_title_and_background_color();
	return (sh.exit_code);
}

/*
	$ mkdir test
	$ cd test
	$ rm -rf ../test
	$ pwd
	/home/libousse/lycoris/test
	$ cd ..

	minishell$ mkdir gab
	minishell$ cd gab
	minishell/gab$ mkdir gab1
	minishell/gab$ cd gab1
	minishell/gab/gab1$ rm -rf ../../gab
	minishell/gab/gab1$ cd ..
		cd: error retrieving current directory: getcwd: cannot access parent 
		directories: No such file or directory
	minishell/gab/gab1/..$ cd ..
	minishell$

	----------------------------------------------------------------------------

	alias egrep='egrep --color=auto'
	alias fgrep='fgrep --color=auto'
	alias grep='grep --color=auto'
	alias ls='ls --color=auto'

	----------------------------------------------------------------------------

	- As for Valgrind flags, check for unclosed FDs with `--track-fds=yes`, and 
	you can add `--trace-children=yes` to find out in which child process you 
	need to close them.

	----------------------------------------------------------------------------

	local vars in external cmd
*/

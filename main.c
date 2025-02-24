/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:14:05 by lchauffo          #+#    #+#             */
/*   Updated: 2025/02/24 13:33:06 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigerrno.h"

int	g_signum;

static void	init_env(t_sh *sh, char **envp);

int	main(int argc, char **argv, char **envp)
{
	t_sh	sh;

	handle_no_tty();
	if (argc > 1)
		return (output_error(EPERM,
				compose_err_msg(SHELL, 0, 0, "Too many arguments")));
	if (!set_signals(0))
		return (1);
	ft_bzero(&sh, sizeof(t_sh));
	handle_default_background_color(0);
	set_background_color(E_GNOME);
	sh.first_arg = argv[0];
	sh.valid_term = is_term_var_valid(&sh);
	sh.pid = ft_itoa(get_pid(&sh, sh.first_arg));
	sh.user = circular_pipeline(&sh, "/bin/whoami");
	sh.host = circular_pipeline(&sh, "/bin/uname -n | /bin/cut -d. -f1");
	sh.home = get_home_path(&sh, sh.user);
	sh.shells = get_shells(&sh);
	sh.color = E_GNOME;
	init_env(&sh, envp);
	run_shell(&sh);
	free_shell(&sh);
	if (sh.subshell == 0)
		reset_title_and_background_color();
	return (sh.exit_code);
}

static void	init_env(t_sh *sh, char **envp)
{
	sh->env = convert_to_lst(envp);
	add_pwd(sh);
	update_shlvl(&sh->env, FALSE);
	return ;
}

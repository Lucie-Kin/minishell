/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subprocess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:38:12 by libousse          #+#    #+#             */
/*   Updated: 2024/11/25 16:53:53 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_subshell(t_sh *sh, t_pl *pl);
static void	run_cmd(t_sh *sh, t_pl *pl, char *cmd_fullpath);
static void	prepare_for_shell_cmd(t_sh *sh, const char *cmd);

int	execute_subprocess(t_sh *sh, t_pl *pl)
{
	char	*cmd_fullpath;

	cmd_fullpath = 0;
	close_unused_pipes(pl->index, pl->fd_pipe, pl->fd_pipe_len);
	if (!redirect_io(pl))
		return (restore_io(pl));
	if (isbuiltin(pl->cmdl[pl->index], sh->local))
	{
		pl->exit_code = execute_builtin(sh);
		return (restore_io(pl));
	}
	if (!ft_strcmp(pl->cmdl[pl->index][0], SEP_STR))
		return (execute_subshell(sh, pl));
	if (!resolve_command(pl, pl->cmdl[pl->index][0], &cmd_fullpath))
		return (restore_io(pl));
	if (cmd_fullpath)
	{
		run_cmd(sh, pl, cmd_fullpath);
		free(cmd_fullpath);
	}
	return (restore_io(pl));
}

static int	execute_subshell(t_sh *sh, t_pl *pl)
{
	size_t	last;
	int		fd_std[2];

	remove_array_elements((void **)pl->cmdl[pl->index], 0, 0, free);
	last = get_array_length((void **)pl->cmdl[pl->index]) - 1;
	remove_array_elements((void **)pl->cmdl[pl->index], last, last, free);
	sh->rl.tokens = (char **)extract_array_elements(
			(void **)pl->cmdl[pl->index], 0, last - 1);
	fd_std[0] = pl->fd_std[0];
	fd_std[1] = pl->fd_std[1];
	destroy_all_ex(sh);
	interpret_and_process_cmd(sh);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	dup2(fd_std[0], STDIN_FILENO);
	close(fd_std[0]);
	dup2(fd_std[1], STDOUT_FILENO);
	close(fd_std[1]);
	return (sh->exit_code);
}

static void	run_cmd(t_sh *sh, t_pl *pl, char *cmd_fullpath)
{
	if (is_shell(sh->shells, cmd_fullpath))
		prepare_for_shell_cmd(sh, cmd_fullpath);
	set_signals(1);
	execve(cmd_fullpath, pl->cmdl[pl->index], convert_to_tab(sh->env));
	pl->exit_code = errno;
	pl->err_msg = compose_err_msg(0, pl->cmdl[pl->index][0], 0,
			strerror(pl->exit_code));
	return ;
}

static void	prepare_for_shell_cmd(t_sh *sh, const char *cmd)
{
	char	*p_slash;

	update_shlvl(&sh->env, FALSE);
	p_slash = ft_strrchr(cmd, '/');
	if (!ft_strcmp(cmd, "minishell")
		|| (p_slash && !ft_strcmp(p_slash + 1, "minishell")))
		handle_default_background_color(1);
	else
		reset_title_and_background_color();
	return ;
}

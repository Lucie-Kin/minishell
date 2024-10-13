/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:23:59 by libousse          #+#    #+#             */
/*   Updated: 2024/10/12 21:33:32 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	run_shell(t_sh *sh)
{
	sh->keep_running = 1;
	sh->exit_code = 0;
	sh->pwd_backup = 0;
	set_pwd_backup(sh, getenv("PWD"));
	init_prompt(sh);
	while (sh->keep_running)
	{
		update_prompt(sh);
		sh->rl.buf = 0;
		add_input_to_buffer(sh, sh->rl.prompt);
		while (sh->rl.buf && sh->rl.buf[0])
			process_current_line(sh);
		free_entire_array((void **)sh->rl.buf, free);
	}
	return ;
}

void	free_shell(t_sh *sh)
{
	free(sh->pid);
	free(sh->pwd_backup);
	// free env
	free(sh->rl.user);
	free(sh->rl.prompt);
	rl_clear_history();
	return ;
}

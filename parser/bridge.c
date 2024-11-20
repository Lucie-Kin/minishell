/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bridge.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:56:54 by libousse          #+#    #+#             */
/*   Updated: 2024/11/19 12:15:30 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	process_cmd(t_sh *sh);

void	interpret_and_process_cmd(t_sh *sh)
{
	interpreter(sh);
	free_entire_array((void **)sh->rl.tokens, free);
	sh->rl.tokens = 0;
	while (sh->ex)
	{
		if (sh->ex->logop == LOGOP_COLON)
			process_cmd(sh);
		else if (sh->ex->logop == LOGOP_OR && sh->exit_code)
			process_cmd(sh);
		else if (sh->ex->logop == LOGOP_AND && !sh->exit_code)
			process_cmd(sh);
		pop_head_ex(sh);
	}
	return ;
}

static void	process_cmd(t_sh *sh)
{
	int	is_only_var;
	int	is_builtin;

	is_only_var = sh->ex->pl.len == 1 && only_var(sh->ex->pl.cmdl[0]);
	is_builtin = sh->ex->pl.len == 1 && isbuiltin(sh->ex->pl.cmdl[0],
			sh->local);
	if (is_only_var || is_builtin)
	{
		if (redirect_io(&sh->ex->pl))
		{
			if (is_only_var)
				update_hidden(&sh->hidden, sh->ex->pl.cmdl[0]);
			else
				sh->exit_code = execute_builtin(sh);
		}
		sh->exit_code = restore_io(&sh->ex->pl);
	}
	else
		sh->exit_code = execute_pipeline(sh);
	return ;
}

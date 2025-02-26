/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bridge.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:56:54 by libousse          #+#    #+#             */
/*   Updated: 2025/02/26 16:38:35 by libousse         ###   ########.fr       */
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
		else if (sh->ex->logop == LOGOP_OR && sh->exit_code
			&& sh->exit_code != 127 + SIGQUIT)
			process_cmd(sh);
		else if (sh->ex->logop == LOGOP_AND && !sh->exit_code)
			process_cmd(sh);
		if (sh->ex->pl.len == 1 && sh->ex->pl.cmdl[0][0] \
		&& !ft_strcmp(sh->ex->pl.cmdl[0][0], "exit"))
			destroy_all_ex(sh);
		else
			pop_head_ex(sh);
	}
	return ;
}

static void	process_cmd(t_sh *sh)
{
	if (sh->ex->pl.len == 1 && only_var(sh->ex->pl.cmdl[0]))
		sh->exit_code = update_hidden(&sh->hidden, sh->ex->pl.cmdl[0]);
	else if (sh->ex->pl.len == 1 && isbuiltin(sh->ex->pl.cmdl[0]))
	{
		if (redirect_io(&sh->ex->pl))
			sh->ex->pl.exit_code = execute_builtin(sh);
		sh->exit_code = restore_io(&sh->ex->pl);
		lst_clear(&sh->local);
	}
	else
		sh->exit_code = execute_pipeline(sh);
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:25:21 by libousse          #+#    #+#             */
/*   Updated: 2024/11/22 14:05:34 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static void	process_current_ex_pl(t_sh *sh, t_ex *ex);

void	interpreter(t_sh *sh)
{
	char	**tmp;
	t_ex	*ex;

	sh->ex = ft_calloc(1, sizeof(t_ex));
	ex = sh->ex;
	while (sh->rl.tokens && sh->rl.tokens[0])
	{
		if (!ex)
			break ;
		ex->logop = get_logop_and_remove_token(sh->rl.tokens);
		tmp = extract_beyond_first_pipeline(sh->rl.tokens);
		process_current_ex_pl(sh, ex);
		if (!ex->pl.cmdl || !ex->pl.inf || !ex->pl.outf)
			break ;
		clean_pl_tokens(&ex->pl);
		free_entire_array((void **)sh->rl.tokens, free);
		sh->rl.tokens = tmp;
		while (!(sh->rl.tokens && sh->rl.tokens[0]))
			return ;
		ex->next = ft_calloc(1, sizeof(t_ex));
		ex = ex->next;
	}
	destroy_all_ex(sh);
	return ;
}

int	pop_head_ex(t_sh *sh)
{
	int		exit_code;
	t_ex	*next;

	if (!sh || !sh->ex)
		return (0);
	exit_code = sh->ex->pl.exit_code;
	next = sh->ex->next;
	free_entire_array((void **)sh->ex->pl.path, free);
	free_entire_array((void **)sh->ex->pl.fd_pipe, free);
	destroy_pl_cmdl(sh->ex->pl.cmdl);
	destroy_pl_inf(sh->ex->pl.inf);
	destroy_pl_outf(sh->ex->pl.outf);
	free(sh->ex);
	sh->ex = next;
	return (exit_code);
}

void	destroy_all_ex(t_sh *sh)
{
	if (!sh)
		return ;
	while (sh->ex)
		pop_head_ex(sh);
	return ;
}

static void	process_current_ex_pl(t_sh *sh, t_ex *ex)
{
	ex->pl.len = get_pl_len(sh->rl.tokens);
	ex->pl.path = get_pl_path(sh);
	ex->pl.fd_pipe_len = ex->pl.len - 1;
	ex->pl.cmdl = get_pl_cmdl(sh->rl.tokens, ex->pl.len);
	ex->pl.inf = get_pl_inf(&ex->pl, duplicate_strings(sh->rl.hd));
	ex->pl.outf = get_pl_outf(&ex->pl);
	return ;
}

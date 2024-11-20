/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:25:21 by libousse          #+#    #+#             */
/*   Updated: 2024/11/20 12:36:29 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	interpreter(t_sh *sh)
{
	/*
	`echo a && (exit && cd .. && ls > out)`
	a
	[out not created]

	`echo a && (exit && cd .. && ls) > out`
	a
	[out created in . but empty]

	`echo a && (cd .. && ls) > out`
	a
	[out created in . and contains the right content]

	`echo a && (cd .. && ls > out)`
	a
	[out created in .. and contains the right content]

	`(echo b && echo a) | sort`
	a
	b

	`((echo b && echo a) | sort) | tr '\n' ' '`
	a b

	---

	$ (exit 2)
	$ echo $?
	2

	$ ls | (aaaaaa)
	$ echo $?
	127
	*/
	
	if (!sh->rl.tokens || !sh->rl.tokens[0])
		return ;
	sh->ex = ft_calloc(1, sizeof(t_ex));
	if (!sh->ex)
		return ;
	sh->ex->pl.len = get_pl_len(sh->rl.tokens);
	sh->ex->pl.path = get_pl_path(sh);
	sh->ex->pl.fd_pipe_len = sh->ex->pl.len - 1;
	sh->ex->pl.cmdl = get_pl_cmdl(sh->rl.tokens, sh->ex->pl.len);
	sh->ex->pl.inf = get_pl_inf(&sh->ex->pl, duplicate_strings(sh->rl.hd));
	sh->ex->pl.outf = get_pl_outf(&sh->ex->pl);
	if (!sh->ex->pl.cmdl || !sh->ex->pl.inf || !sh->ex->pl.outf)
	{
		free_entire_array((void **)sh->ex->pl.path, free);
		destroy_pl_cmdl(sh->ex->pl.cmdl);
		destroy_pl_inf(sh->ex->pl.inf);
		destroy_pl_outf(sh->ex->pl.outf);
		return ;
	}
	clean_pl_tokens(&sh->ex->pl);
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

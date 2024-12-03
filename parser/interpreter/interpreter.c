/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:25:21 by libousse          #+#    #+#             */
/*   Updated: 2024/12/03 23:33:31 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	process_current_ex_pl(t_sh *sh, t_ex *ex);
static void	replace_delimiters_by_filenames(t_sh *sh);

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
		if (!ex->pl.cmdl || !ex->pl.file)
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
	destroy_pl_file(sh->ex->pl.file);
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
	replace_delimiters_by_filenames(sh);
	ex->pl.cmdl = get_pl_cmdl(sh->rl.tokens, ex->pl.len);
	ex->pl.file = get_pl_file(&ex->pl);
	return ;
}

static void	replace_delimiters_by_filenames(t_sh *sh)
{
	size_t	i;
	char	**hd_dup;
	char	*extracted;

	hd_dup = duplicate_strings(sh->rl.hd);
	if (!hd_dup)
		return ;
	i = 0;
	while (sh->rl.tokens[i])
	{
		if (!ft_strcmp(sh->rl.tokens[i], "<<"))
		{
			extracted = (char *)extract_array_element((void **)hd_dup, 0);
			if (extracted)
			{
				free(sh->rl.tokens[i + 1]);
				sh->rl.tokens[i + 1] = extracted;
			}
		}
		++i;
	}
	free_entire_array((void **)hd_dup, free);
	return ;
}

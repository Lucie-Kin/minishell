/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:23:59 by libousse          #+#    #+#             */
/*   Updated: 2024/10/24 19:53:37 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	process_current_line(t_sh *sh);
static void	unlink_heredocs(t_sh *sh);

void	run_shell(t_sh *sh)
{
	sh->keep_running = TRUE;
	init_prompt(sh);
	while (sh->keep_running)
	{
		update_prompt(sh);
		add_input_to_buffer(sh, sh->rl.prompt);
		while (sh->rl.buf && sh->rl.buf[0])
			process_current_line(sh);
		free_entire_array((void **)sh->rl.buf, free);
		sh->rl.buf = 0;
	}
	return ;
}

void	free_shell(t_sh *sh)
{
	close(STDIN_FILENO);
	readline("\001\e]0;Terminal\a\002");
	rl_clear_history();
	lst_clear(&sh->env);
	lst_clear(&sh->hidden);
	lst_clear(&sh->local);
	free(sh->pid);
	free(sh->user);
	free(sh->host);
	free(sh->home);
	free(sh->rl.user);
	free(sh->rl.prompt);
	free_entire_array((void **)sh->rl.buf, free);
	free_entire_array((void **)sh->rl.arr, free_rl_arr_element);
	free_entire_array((void **)sh->rl.tokens, free);
	free_entire_array((void **)sh->rl.hd, free);
	return ;
}

void	free_rl_arr_element(void *ptr)
{
	size_t		i;
	t_rl_arr	*elem;

	if (!ptr)
		return ;
	elem = ptr;
	free(elem->value);
	if (elem->delimiters)
	{
		i = 0;
		while (elem->delimiters[i])
		{
			free(elem->delimiters[i]);
			++i;
		}
		free(elem->delimiters);
	}
	free(elem);
	return ;
}

static void	process_cmd(t_sh *sh)
{
	while (sh->ex)
	{
		if (sh->ex->pl.len == 1 && only_var(sh->ex->pl.cmdl[0]))
			update_hidden(&sh->hidden, sh->ex->pl.cmdl[0]);
		else if (sh->ex->pl.len == 1
			&& isbuiltin(sh->ex->pl.cmdl[0], sh->local))
			sh->exit_code = execute_builtin(&sh->env, &sh->hidden, &sh->local,
					sh->ex->pl.cmdl[0]);
		else
			sh->exit_code = execute_pipeline(sh);
		pop_head_ex(sh);
	}
}

static void	process_current_line(t_sh *sh)
{
	char	*cmdl;
	int		is_legal;

	is_legal = extract_first_command_line(sh);
	append_heredoc_lines_with_a_newline_char(sh);
	add_input_to_history(sh);
	if (is_legal)
	{
		cmdl = concatenate_all_cmdl_lines(sh);
		sh->rl.tokens = tokenize(cmdl, 1, ft_isspace);
		free(cmdl);
		expansion(sh);
		interpreter(sh);
		free_entire_array((void **)sh->rl.tokens, free);
		sh->rl.tokens = 0;
		process_cmd(sh);
	}
	unlink_heredocs(sh);
	free_entire_array((void **)sh->rl.arr, free_rl_arr_element);
	sh->rl.arr = 0;
	free_entire_array((void **)sh->rl.hd, free);
	sh->rl.hd = 0;
	return ;
}

static void	unlink_heredocs(t_sh *sh)
{
	size_t	i;

	if (!sh->rl.hd)
		return ;
	i = 0;
	while (sh->rl.hd[i])
	{
		unlink(sh->rl.hd[i]);
		++i;
	}
	return ;
}

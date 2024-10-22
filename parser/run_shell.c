/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:23:59 by libousse          #+#    #+#             */
/*   Updated: 2024/10/22 13:49:31 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	process_current_line(t_sh *sh);
static void	unlink_heredocs(t_sh *sh);

void	run_shell(t_sh *sh)
{
	sh->keep_running = TRUE;
	set_pwd_backup(sh, getenv("PWD"));
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
	rl_clear_history();
	free(sh->pid);
	free(sh->pwd_backup);
	// free env
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
		while (sh->ex)
		{
			sh->exit_code = execute_pipeline(sh);
			pop_head_ex(sh);
		}
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

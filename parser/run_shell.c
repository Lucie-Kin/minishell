/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:23:59 by libousse          #+#    #+#             */
/*   Updated: 2024/11/28 17:01:04 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	process_current_line(t_sh *sh);

void	run_shell(t_sh *sh)
{
	sh->keep_running = TRUE;
	init_prompt(sh);
	while (sh->subshell == 0 && sh->keep_running)
	{
		update_prompt(sh);
		set_bg_color(&sh->color);
		add_input_to_buffer(sh, sh->rl.prompt);
		while (sh->keep_running && sh->rl.buf && sh->rl.buf[0])
			process_current_line(sh);
		if (g_signum == EOF)
			handle_ctrl_d(sh, NULL);
		free_entire_array((void **)sh->rl.buf, free);
		sh->rl.buf = NULL;
	}
	return ;
}

void	free_shell(t_sh *sh)
{
	if (!sh)
		return ;
	rl_clear_history();
	lst_clear(&sh->env);
	lst_clear(&sh->hidden);
	free(sh->pwd->key);
	if (sh->pwd->value)
		free(sh->pwd->value);
	free(sh->pwd);
	free(sh->pid);
	free(sh->user);
	free(sh->host);
	free(sh->home);
	free(sh->shells);
	free(sh->rl.user);
	free(sh->rl.prompt);
	free_entire_array((void **)sh->rl.buf, free);
	free_entire_array((void **)sh->rl.arr, free_rl_arr_element);
	free_entire_array((void **)sh->rl.tokens, free);
	free_entire_array((void **)sh->rl.hd, free);
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
	add_input_to_history(sh);
	if (g_signum == EOF)
		handle_ctrl_d(sh, &is_legal);
	g_signum = 0;
	if (is_legal)
	{
		cmdl = concatenate_all_cmdl_lines(sh);
		sh->rl.tokens = tokenize(cmdl, 1, ft_isspace);
		free(cmdl);
		expansion(sh);
		interpret_and_process_cmd(sh);
	}
	unlink_heredocs(sh);
	free_entire_array((void **)sh->rl.arr, free_rl_arr_element);
	sh->rl.arr = 0;
	free_entire_array((void **)sh->rl.hd, free);
	sh->rl.hd = 0;
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:42:07 by libousse          #+#    #+#             */
/*   Updated: 2024/11/12 15:55:05 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static void	cut_input_into_lines(t_sh *sh, char *input);
static char	*place_split_points_for_input(char *input);

void	add_input_to_buffer(t_sh *sh, const char *prompt)
{
	char	*input;

	if (!ft_strcmp(prompt, "> "))
		set_signal_handling(SIGINT, signal_handler_extra);
	input = readline(prompt);
	set_signal_handling(SIGINT, signal_handler);
	if (!input)
	{
		update_sig_var(EOF);
		return ;
	}
	else if (g_signum == SIGINT)
	{
		free_entire_array((void **)sh->rl.buf, free);
		sh->rl.buf = 0;
	}
	cut_input_into_lines(sh, input);
	return ;
}

static void	cut_input_into_lines(t_sh *sh, char *input)
{
	char	**lines;

	input = place_split_points_for_input(input);
	if (!input)
		return ;
	lines = ft_split(input, SEP);
	free(input);
	insert_array_elements((void ***)&sh->rl.buf, (void **)lines,
		get_array_length((void **)sh->rl.buf));
	if (!sh->rl.buf)
		sh->exit_code = output_error(ENOMEM, compose_err_msg(SHELL, "readline",
					0, strerror(ENOMEM)));
	return ;
}

static char	*place_split_points_for_input(char *input)
{
	char	*tmp;
	char	*p_newline;

	tmp = ft_strjoin(input, "\n");
	free(input);
	input = tmp;
	if (!input)
		return (0);
	p_newline = ft_strchr(input, '\n');
	while (p_newline)
	{
		tmp = insert_str_before_char(input, p_newline - input + 1, SEP_STR);
		p_newline = tmp + (p_newline - input + 1);
		free(input);
		input = tmp;
		if (!input)
			break ;
		p_newline = ft_strchr(p_newline + 1, '\n');
	}
	return (input);
}

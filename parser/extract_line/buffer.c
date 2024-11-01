/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:42:07 by libousse          #+#    #+#             */
/*   Updated: 2024/11/01 17:58:30 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static char	*place_split_points_for_input(char *input);

void	add_input_to_buffer(t_sh *sh, const char *prompt)
{
	char	*input;
	char	**lines;

	input = readline(prompt);
	// `readline` only returns null when Ctrl-D in an empty line
	if (!input)
		return ;
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

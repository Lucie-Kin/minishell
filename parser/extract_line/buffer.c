/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:42:07 by libousse          #+#    #+#             */
/*   Updated: 2024/10/22 14:56:15 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	add_input_to_buffer(t_sh *sh, const char *prompt)
{
		/*
			- In add_input_to_buffer, don't just split at '\n'. When a '\n' is 
			right after another, you add an empty line to the buffer instead of 
			making it disappear.
			- Outside of heredoc content, just ignore these empty lines. They 
			must not appear in history.
			- In heredoc content, you'll add '\n' at the end of them like any 
			other line.
			- During heredoc prompting, you can differentiate between a nullptr 
			in readline being caused by Enter and by Ctrl-D thanks to a signal. 
			By default, if the buffer was empty, and nullptr happens, of course 
			don't add a new empty line. But, same thing if we're prompting for 
			input outside of heredoc content. Only add an empty line in the 
			context of heredocs, and in a multiline input (indeed, we cannot 
			take the risk to prune empty lines and have heredoc empty lines be 
			removed by mistake).
			- EDIT: I may have noticed that, when prompting for an unclosed 
			quote, empty lines are kept.
		*/
	char	*input;
	char	**lines;

	input = readline(prompt);
	if (!input)
		return ;
	lines = ft_split(input, '\n');
	free(input);
	insert_array_elements((void ***)&sh->rl.buf, (void **)lines,
		get_array_length((void **)sh->rl.buf));
	if (!sh->rl.buf)
		sh->exit_code = output_error(ENOMEM, compose_err_msg(SHELL_NAME,
					"readline", strerror(ENOMEM)));
	return ;
}

void	extract_first_buffer_line(t_sh *sh, size_t *index, int is_heredoc)
{
	t_rl_arr	*elem;

	elem = ft_calloc(1, sizeof(t_rl_arr));
	if (!elem)
		return ;
	if (!sh->rl.buf[0])
		elem->value = ft_strdup("");
	else
		elem->value = extract_array_element((void **)sh->rl.buf, 0);
	elem->is_heredoc = is_heredoc;
	insert_array_element((void ***)&sh->rl.arr, elem, *index);
	if (!sh->rl.arr[*index])
		return ;
	concatenate_with_previous_line(sh, index);
	if (sh->rl.arr[*index]->is_heredoc)
		return ;
	sh->rl.arr[*index]->delimiters = get_delimiters(sh->rl.arr[*index]->value);
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:06:34 by libousse          #+#    #+#             */
/*   Updated: 2024/10/12 18:12:27 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	add_input_to_buffer(t_sh *sh, const char *prompt)
{
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
		sh->exit_code = output_error_UPDATE(ENOMEM, compose_err_msg(SHELL_NAME,
					"readline", strerror(ENOMEM)));
	return ;
}

void	append_heredoc_lines_with_a_newline_char(t_sh *sh)
{
	size_t	i;
	char	*tmp;

	if (!sh->rl.arr)
		return ;
	i = 0;
	while (sh->rl.arr[i])
	{
		if (sh->rl.arr[i]->is_heredoc)
		{
			tmp = ft_strjoin(sh->rl.arr[i]->value, "\n");
			if (tmp)
			{
				free(sh->rl.arr[i]->value);
				sh->rl.arr[i]->value = tmp;
			}
		}
		++i;
	}
	return ;
}

char	*concatenate_all_cmdl_lines(t_sh *sh)
{
	size_t	i;
	char	*tmp;
	char	*cmdl;

	if (!sh->rl.arr)
		return (0);
	cmdl = ft_strdup(sh->rl.arr[0]->value);
	if (!cmdl)
		return (0);
	i = 1;
	while (sh->rl.arr[i])
	{
		if (!sh->rl.arr[i]->is_heredoc)
		{
			tmp = ft_strjoin(cmdl, sh->rl.arr[i]->value);
			if (!tmp)
				return (cmdl);
			free(cmdl);
			cmdl = tmp;
		}
		++i;
	}
	return (cmdl);
}

char	*concatenate_all_heredoc_lines(t_sh *sh)
{
	size_t	i;
	char	*tmp;
	char	*heredocs;

	if (!sh->rl.arr)
		return (0);
	i = 0;
	heredocs = 0;
	while (sh->rl.arr[i])
	{
		if (!heredocs && sh->rl.arr[i]->is_heredoc)
			heredocs = ft_strdup(sh->rl.arr[i]->value);
		else if (sh->rl.arr[i]->is_heredoc)
		{
			tmp = ft_strjoin(heredocs, sh->rl.arr[i]->value);
			if (!tmp)
				return (heredocs);
			free(heredocs);
			heredocs = tmp;
		}
		++i;
	}
	return (heredocs);
}

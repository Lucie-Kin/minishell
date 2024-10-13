/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_first_command_line.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:22:28 by libousse          #+#    #+#             */
/*   Updated: 2024/10/11 14:04:45 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	add_prefix_to_first_buffer_line(t_sh *sh, char *prefix);
static void	extract_first_buffer_line(t_sh *sh, size_t *i, int is_heredoc);
static int	check_need_for_input(t_sh *sh, size_t index, char **prefix,
				int *is_for_heredoc);

int	extract_first_command_line(t_sh *sh)
{
	size_t	index;
	char	*extra_line_prefix;
	int		is_extra_line_needed;
	int		is_extra_line_heredoc;

	index = 0;
	extra_line_prefix = 0;
	is_extra_line_needed = 1;
	is_extra_line_heredoc = 0;
	while (is_extra_line_needed)
	{
		add_prefix_to_first_buffer_line(sh, extra_line_prefix);
		extract_first_buffer_line(sh, &index, is_extra_line_heredoc);
		if (!check_for_syntax_errors(sh->rl.arr[index]->value))
		{
			sh->exit_code = 2;
			return (0);
		}
		is_extra_line_needed = check_need_for_input(sh, index,
				&extra_line_prefix, &is_extra_line_heredoc);
		if (is_extra_line_needed && !sh->rl.buf[0])
			add_input_to_buffer(sh, "> ");
		++index;
	}
	return (1);
}

static void	add_prefix_to_first_buffer_line(t_sh *sh, char *prefix)
{
	char	*tmp;
	char	**delimiters;

	if (!sh->rl.buf[0])
		return ;
	if (prefix && !ft_strcmp(prefix, " "))
	{
		delimiters = get_delimiters(sh->rl.buf[0]);
		if (delimiters)
			prefix = "\n";
		free_entire_array((void **)delimiters, free);
	}
	tmp = ft_strjoin(prefix, sh->rl.buf[0]);
	if (!tmp)
		return ;
	free(sh->rl.buf[0]);
	sh->rl.buf[0] = tmp;
	return ;
}

static void	extract_first_buffer_line(t_sh *sh, size_t *i, int is_heredoc)
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
	insert_array_element((void ***)&sh->rl.arr, elem, *i);
	concatenate_with_previous_line(sh, i);
	if (!sh->rl.arr[*i]->is_heredoc)
		sh->rl.arr[*i]->delimiters = get_delimiters(sh->rl.arr[*i]->value);
	return ;
}

static int	check_need_for_input(t_sh *sh, size_t index, char **prefix,
	int *is_extra_line_heredoc)
{
	int	is_needed;

	*is_extra_line_heredoc = 0;
	is_needed = 0;
	if (!sh->rl.arr[index]->is_heredoc
		&& find_unclosed_quote(sh->rl.arr[index]->value))
	{
		is_needed = 1;
		*prefix = "\n";
	}
	if (!is_needed)
	{
		*prefix = get_prefix_for_backslashes(sh, index, &is_needed);
		if (is_needed && sh->rl.arr[index]->is_heredoc)
		{
			*is_extra_line_heredoc = 1;
			*prefix = 0;
		}
	}
	if (!is_needed)
		is_needed = !left_to_right_check(sh, prefix, is_extra_line_heredoc);
	return (is_needed);
}

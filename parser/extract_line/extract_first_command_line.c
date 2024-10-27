/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_first_command_line.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:22:28 by libousse          #+#    #+#             */
/*   Updated: 2024/10/26 23:03:02 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static void	add_prefix_to_first_buffer_line(t_sh *sh, char *prefix);
static int	check_need_for_input(t_sh *sh, size_t *index, char **prefix,
				int *is_legal);

int	extract_first_command_line(t_sh *sh)
{
	size_t	index;
	char	*prefix;
	int		is_legal;
	int		is_needed;

	index = 0;
	prefix = 0;
	is_legal = 1;
	is_needed = 1;
	while (is_legal && is_needed)
	{
		add_prefix_to_first_buffer_line(sh, prefix);
		extract_first_buffer_line(sh, &index, 0);
		is_needed = check_need_for_input(sh, &index, &prefix, &is_legal);
		if (is_legal && is_needed && !sh->rl.buf[0])
			add_input_to_buffer(sh, "> ");
		++index;
	}
	return (is_legal);
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

static int	check_need_for_input(t_sh *sh, size_t *index, char **prefix,
	int *is_legal)
{
	int	is_needed;

	if (!sh->rl.arr[*index])
		return (0);
	else if (find_unclosed_quote(sh->rl.arr[*index]->value))
	{
		*prefix = "\n";
		return (1);
	}
	/*
		Check for errors here.
		If error there is, set `is_legal` to false and `sh->exit_code` to 2.
	*/
	is_needed = 0;
	*prefix = get_prefix_for_backslashes(sh, *index, &is_needed);
	if (!is_needed)
	{
		*is_legal = handle_heredoc_content(sh, index);
		if (!is_legal)
			return (0);
		is_needed = !check_right_operand_and_parentheses(sh, prefix);
	}
	return (is_needed);
}

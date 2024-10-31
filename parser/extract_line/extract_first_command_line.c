/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_first_command_line.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:22:28 by libousse          #+#    #+#             */
/*   Updated: 2024/10/31 18:09:20 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static void	add_prefix_to_first_buffer_line(t_sh *sh, char *prefix);
static int	check_need_for_input(t_sh *sh, size_t *index, char **prefix,
				int *is_legal);
static int	handle_heredoc_content(t_sh *sh, size_t index);
static void	concatenate_even_if_illegal(t_sh *sh, size_t *index);

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
		is_legal = check_for_syntax_errors(sh, index);
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

	is_needed = 0;
	if (!sh->rl.arr[*index])
		return (0);
	else if (!*is_legal)
		handle_heredoc_content(sh, *index);
	else if (find_unclosed_quote(sh->rl.arr[*index]->value))
	{
		*prefix = "\n";
		is_needed = 1;
	}
	if (!is_needed)
		*prefix = get_prefix_for_backslashes(sh, *index, &is_needed);
	if (*is_legal && !is_needed)
	{
		*is_legal = handle_heredoc_content(sh, *index);
		if (!*is_legal)
			return (0);
		is_needed = !check_right_operand_and_parentheses(sh, prefix);
	}
	if (!*is_legal)
		concatenate_even_if_illegal(sh, index);
	*index = get_array_length((void **)sh->rl.arr) - 1;
	return (is_needed);
}

static int	handle_heredoc_content(t_sh *sh, size_t index)
{
	size_t	i;
	size_t	i_hd;
	size_t	cmdl_index;

	cmdl_index = index;
	if (!sh->rl.arr[cmdl_index]->delimiters)
		return (1);
	i = 0;
	i_hd = get_array_length((void **)sh->rl.hd);
	while (sh->rl.arr[cmdl_index]->delimiters[i])
	{
		if (!create_heredoc(sh, i_hd, &index,
				sh->rl.arr[cmdl_index]->delimiters[i]))
		{
			if (sh->rl.hd[i_hd])
			{
				unlink(sh->rl.hd[i_hd]);
				remove_array_elements((void **)sh->rl.hd, i_hd, i_hd, free);
			}
			return (0);
		}
		++i;
		++i_hd;
	}
	return (1);
}

static void	concatenate_even_if_illegal(t_sh *sh, size_t *index)
{
	size_t	len;

	if (!sh->rl.arr[*index]->value)
		return ;
	len = ft_strlen(sh->rl.arr[*index]->value);
	if (sh->rl.arr[*index]->backslashes == 1
		&& len > 1 && !ft_isspace(sh->rl.arr[*index]->value[len - 2]))
	{
		++*index;
		concatenate_with_previous_line(sh, index);
		return ;
	}
	sh->rl.arr[*index]->backslashes = -1;
	if (sh->rl.arr[*index]->delimiters)
		sh->rl.arr[*index]->value[len - 1] = 0;
	return ;
}

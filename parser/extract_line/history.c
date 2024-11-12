/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:45:00 by libousse          #+#    #+#             */
/*   Updated: 2024/11/12 14:34:13 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static void		remove_unused_newline_chars(t_rl_arr **rl_arr);
static void		remove_nl_if_only_one_and_unclosed_quote(char *s);
static size_t	find_index_of_first_heredoc_line(t_sh *sh);
static char		*concatenate_all_input_lines(t_sh *sh);

void	add_input_to_history(t_sh *sh)
{
	size_t	i;
	char	*hist;
	char	*original_first_heredoc_line;

	if (!sh->rl.arr)
		return ;
	remove_unused_newline_chars(sh->rl.arr);
	original_first_heredoc_line = 0;
	i = find_index_of_first_heredoc_line(sh);
	if (sh->rl.arr[i] && i && !ft_strchr(sh->rl.arr[i - 1]->value, '\n')
		&& !(sh->rl.arr[i - 1]->backslashes % 2))
	{
		original_first_heredoc_line = sh->rl.arr[i]->value;
		sh->rl.arr[i]->value = ft_strjoin("\n", sh->rl.arr[i]->value);
	}
	hist = concatenate_all_input_lines(sh);
	if (hist && hist[0])
		add_history(hist);
	free(hist);
	if (original_first_heredoc_line)
	{
		free(sh->rl.arr[i]->value);
		sh->rl.arr[i]->value = original_first_heredoc_line;
	}
	return ;
}

static void	remove_unused_newline_chars(t_rl_arr **rl_arr)
{
	size_t	i;
	char	*p_nl;

	i = 0;
	while (rl_arr[i])
	{
		if (!rl_arr[i]->is_heredoc)
		{
			p_nl = ft_strchr(rl_arr[i]->value, '\n');
			while (p_nl)
			{
				if (is_char_within_quotes(rl_arr[i]->value, p_nl))
					p_nl = ft_strchr(p_nl + 1, '\n');
				else
				{
					ft_memmove(p_nl, p_nl + 1, ft_strlen(p_nl + 1) + 1);
					p_nl = ft_strchr(p_nl, '\n');
				}
			}
			remove_nl_if_only_one_and_unclosed_quote(rl_arr[i]->value);
		}
		++i;
	}
	return ;
}

static void	remove_nl_if_only_one_and_unclosed_quote(char *s)
{
	size_t	amount;
	char	*p_nl;
	char	*p_first_nl;

	if (!find_unclosed_quote(s))
		return ;
	amount = 0;
	p_nl = ft_strchr(s, '\n');
	p_first_nl = p_nl;
	while (p_nl)
	{
		++amount;
		p_nl = ft_strchr(p_nl + 1, '\n');
	}
	if (!p_first_nl || amount != 1)
		return ;
	*p_first_nl = 0;
	return ;
}

static size_t	find_index_of_first_heredoc_line(t_sh *sh)
{
	size_t	i;

	i = 0;
	while (sh->rl.arr[i])
	{
		if (sh->rl.arr[i]->is_heredoc)
			break ;
		++i;
	}
	return (i);
}

static char	*concatenate_all_input_lines(t_sh *sh)
{
	size_t	i;
	char	*joined;
	char	*tmp;

	if (!sh->rl.arr)
		return (0);
	joined = ft_strdup(sh->rl.arr[0]->value);
	i = 1;
	while (sh->rl.arr[i])
	{
		tmp = joined;
		joined = ft_strjoin(tmp, sh->rl.arr[i]->value);
		free(tmp);
		++i;
	}
	return (joined);
}

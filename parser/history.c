/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:45:00 by libousse          #+#    #+#             */
/*   Updated: 2024/10/14 16:46:12 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static size_t	find_index_of_first_heredoc_line(t_sh *sh);
static char		*concatenate_all_input_lines(t_sh *sh);

void	add_input_to_history(t_sh *sh)
{
	size_t	i;
	char	*hist;
	char	*original_first_heredoc_line;

	if (!sh->rl.arr)
		return ;
	original_first_heredoc_line = 0;
	i = find_index_of_first_heredoc_line(sh);
	if (sh->rl.arr[i] && i && !ft_strchr(sh->rl.arr[i - 1]->value, '\n')
		&& !(sh->rl.arr[i - 1]->backslashes % 2))
	{
		original_first_heredoc_line = sh->rl.arr[i]->value;
		sh->rl.arr[i]->value = ft_strjoin("\n", sh->rl.arr[i]->value);
	}
	hist = concatenate_all_input_lines(sh);
	add_history(hist);
	free(hist);
	if (original_first_heredoc_line)
	{
		free(sh->rl.arr[i]->value);
		sh->rl.arr[i]->value = original_first_heredoc_line;
	}
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

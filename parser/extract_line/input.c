/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:06:34 by libousse          #+#    #+#             */
/*   Updated: 2024/10/22 14:58:37 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

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

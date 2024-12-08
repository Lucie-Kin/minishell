/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:45:59 by libousse          #+#    #+#             */
/*   Updated: 2024/12/08 17:43:18 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	**get_expanded_token(t_sh *sh, const char *s);

/*
	- Expand tilde: `~`, `~+` and `~-`.
	- Expand special parameters: `$0`, `$$` and `$?`.
	- Expand environment variables.
	- Expand asterisk wildcards.
*/

void	expansion(t_sh *sh)
{
	size_t	i;
	size_t	expanded_len;
	char	**expanded;

	if (!sh->rl.tokens)
		return ;
	i = 0;
	while (sh->rl.tokens[i])
	{
		expanded = get_expanded_token(sh, sh->rl.tokens[i]);
		expanded_len = get_array_length((void **)expanded);
		remove_array_elements((void **)sh->rl.tokens, i, i, free);
		if (!expanded_len || !expanded[0][0])
			free_entire_array((void **)expanded, free);
		else
		{
			insert_array_elements((void ***)&sh->rl.tokens, (void **)expanded,
				i);
			i += expanded_len;
		}
	}
	return ;
}

static char	**get_expanded_token(t_sh *sh, const char *s)
{
	size_t	i;
	char	**arr;
	char	**tmp;

	if (!s)
		return (0);
	arr = expand_tilde(sh, s);
	if (arr)
		return (arr);
	arr = expand_environment_variables(sh, s);
	if (!arr)
		return (expand_asterisk_wildcard(s));
	i = 0;
	while (arr[i])
	{
		tmp = expand_asterisk_wildcard(arr[i]);
		if (!insert_array_elements((void ***)&arr, (void **)tmp, i++))
			free_entire_array((void **)tmp, free);
		else
		{
			remove_array_elements((void **)arr, i - 1, i - 1, free);
			i += get_array_length((void **)tmp) - 1;
		}
	}
	return (arr);
}

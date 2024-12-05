/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:45:59 by libousse          #+#    #+#             */
/*   Updated: 2024/12/05 11:02:11 by lchauffo         ###   ########.fr       */
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

/*
	TODO:

	export A="ls -l"
	$A
	-> Should execute `ls -l`
*/
static char	**get_expanded_token(t_sh *sh, const char *s)
{
	char	**arr;
	char	*tmp;

	if (!s)
		return (0);
	arr = 0;
	tmp = expand_tilde(sh, s);
	if (tmp)
	{
		insert_array_element((void ***)&arr, (void **)tmp, 0);
		return (arr);
	}
	tmp = expand_environment_variables(sh, s);
	if (!tmp)
		return (0);
	arr = expand_asterisk_wildcard(tmp);
	if (arr)
	{
		free(tmp);
		return (arr);
	}
	insert_array_element((void ***)&arr, (void **)tmp, 0);
	return (arr);
}

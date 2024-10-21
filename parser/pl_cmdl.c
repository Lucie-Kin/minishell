/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_cmdl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:54:43 by libousse          #+#    #+#             */
/*   Updated: 2024/10/18 23:24:07 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	**extract_cmdl_element(t_sh *sh, size_t *i);

char	***get_pl_cmdl(t_sh *sh, size_t len)
{
	size_t	i;
	size_t	j;
	char	***cmdl;

	cmdl = ft_calloc(len + 1, sizeof(char **));
	if (!cmdl)
		return (0);
	i = 0;
	j = 0;
	while (sh->rl.tokens[i])
	{
		if (i && !ft_strcmp(sh->rl.tokens[i], "|"))
		{
			cmdl[j] = extract_cmdl_element(sh, &i);
			if (!cmdl[j])
				return (destroy_pl_cmdl(cmdl));
			++j;
		}
		else
			++i;
	}
	cmdl[j] = extract_cmdl_element(sh, &i);
	if (!cmdl[j])
		return (destroy_pl_cmdl(cmdl));
	return (cmdl);
}

void	*destroy_pl_cmdl(char ***cmdl)
{
	size_t	i;

	if (!cmdl)
		return (0);
	i = 0;
	while (cmdl[i])
	{
		free_entire_array((void **)cmdl[i], free);
		++i;
	}
	free(cmdl);
	return (0);
}

static char	**extract_cmdl_element(t_sh *sh, size_t *i)
{
	char	**elem;

	elem = (char **)extract_array_elements((void **)sh->rl.tokens, 0, *i - 1);
	if (!elem)
		return (0);
	*i = 0;
	if (sh->rl.tokens[*i])
		remove_array_elements((void **)sh->rl.tokens, *i, *i, free);
	return (elem);
}

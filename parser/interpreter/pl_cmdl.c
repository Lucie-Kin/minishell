/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_cmdl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:54:43 by libousse          #+#    #+#             */
/*   Updated: 2024/10/22 15:47:48 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static char	**extract_cmdl_element(char	**tokens, size_t *i);

char	***get_pl_cmdl(char	**tokens, size_t len)
{
	size_t	i;
	size_t	j;
	char	***cmdl;

	cmdl = ft_calloc(len + 1, sizeof(char **));
	if (!cmdl)
		return (0);
	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (i && !ft_strcmp(tokens[i], "|"))
		{
			cmdl[j] = extract_cmdl_element(tokens, &i);
			if (!cmdl[j])
				return (destroy_pl_cmdl(cmdl));
			++j;
		}
		else
			++i;
	}
	cmdl[j] = extract_cmdl_element(tokens, &i);
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

static char	**extract_cmdl_element(char **tokens, size_t *i)
{
	char	**elem;

	elem = (char **)extract_array_elements((void **)tokens, 0, *i - 1);
	if (!elem)
		return (0);
	*i = 0;
	if (tokens[*i])
		remove_array_elements((void **)tokens, *i, *i, free);
	return (elem);
}

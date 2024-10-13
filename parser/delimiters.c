/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:05:18 by libousse          #+#    #+#             */
/*   Updated: 2024/10/08 12:37:20 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	update_delimiter_to_clean_version(char **delimiter);
static char	**free_array_if_empty(char **tokens);

char	**get_delimiters(const char *s)
{
	size_t	i;
	char	**tokens;

	tokens = tokenize(s, 1, ft_isspace);
	if (!tokens)
		return (0);
	i = 0;
	while (tokens[i])
	{
		if (!ft_strcmp(tokens[i], "<<"))
		{
			if (!tokens[i + 1] || !ft_strcmp(tokens[i + 1], "<<"))
			{
				remove_array_elements((void **)tokens, i,
					get_array_length((void **)tokens) - 1, free);
				return (free_array_if_empty(tokens));
			}
			update_delimiter_to_clean_version(tokens + i + 1);
			remove_array_elements((void **)tokens, i, i, free);
			++i;
		}
		else
			remove_array_elements((void **)tokens, i, i, free);
	}
	return (free_array_if_empty(tokens));
}

static void	update_delimiter_to_clean_version(char **delimiter)
{
	char	*tmp;

	if (!delimiter || !*delimiter)
		return ;
	tmp = get_clean_token(*delimiter);
	free(*delimiter);
	*delimiter = tmp;
	return ;
}

static char	**free_array_if_empty(char **tokens)
{
	if (!tokens[0])
	{
		free(tokens);
		return (0);
	}
	return (tokens);
}

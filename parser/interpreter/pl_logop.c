/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_logop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:55:04 by libousse          #+#    #+#             */
/*   Updated: 2024/11/21 15:34:13 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int	get_logop_and_remove_token(char **tokens)
{
	int	logop;

	if (!tokens || !tokens[0])
		return (LOGOP_COLON);
	else if (!ft_strcmp(tokens[0], ";"))
		logop = LOGOP_COLON;
	else if (!ft_strcmp(tokens[0], "||"))
		logop = LOGOP_OR;
	else if (!ft_strcmp(tokens[0], "&&"))
		logop = LOGOP_AND;
	else
		return (LOGOP_COLON);
	remove_array_elements((void **)tokens, 0, 0, free);
	return (logop);
}

char	**extract_beyond_first_pipeline(char **tokens)
{
	size_t	i;

	if (!tokens || !tokens[0])
		return (0);
	i = 0;
	while (pl_skip_parentheses(tokens, &i))
	{
		if (!ft_strcmp(tokens[i], ";") || !ft_strcmp(tokens[i], "||")
			|| !ft_strcmp(tokens[i], "&&"))
		{
			if (!tokens[i + 1])
			{
				remove_array_elements((void **)tokens, i, i, free);
				break ;
			}
			return ((char **)extract_array_elements((void **)tokens, i,
					get_array_length((void **)tokens) - 1));
		}
		++i;
	}
	return (0);
}

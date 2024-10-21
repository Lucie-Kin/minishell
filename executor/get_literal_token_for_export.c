/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_literal_token_for_export.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:13:56 by libousse          #+#    #+#             */
/*   Updated: 2024/10/05 23:30:11 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	This function is meant for the export builtin. Store variable values in 
	this format after the parser is done "cleaning" them.
*/
char	*get_literal_token(const char *s)
{
	size_t	i;
	char	*parsed;
	char	*tmp;

	parsed = ft_strdup(s);
	if (!parsed)
		return (0);
	i = 0;
	while (parsed[i])
	{
		if (parsed[i] == '"' || parsed[i] == '$' || parsed[i] == '\\'
			|| parsed[i] == '`')
		{
			tmp = insert_str_before_char(parsed, i, "\\");
			free(parsed);
			parsed = tmp;
			++i;
		}
		++i;
	}
	return (parsed);
}

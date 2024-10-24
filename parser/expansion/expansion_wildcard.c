/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_wildcard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:10:37 by libousse          #+#    #+#             */
/*   Updated: 2024/10/24 11:03:18 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static char	**expand_asterisk_wildcard(const char *s);

char	**expand_wildcard(const char *s)
{
	return (expand_asterisk_wildcard(s));
}

static char	**expand_asterisk_wildcard(const char *s)
{
	char	*p_char;

	if (ft_strchr(s, '"') || ft_strchr(s, '\''))
		return (0);
	p_char = ft_strchr(s, '*');
	
	if (p_char)
	{
		size_t i = 0;
		char **wildcards = get_wildcards(s);
		printf("[WILDCARD] ");
		while (wildcards[i])
		{
			printf("%s ", wildcards[i]);
			++i;
		}
		printf("\n");
	}

	while (p_char)
	{
		if (p_char == s || *(p_char - 1) != '\\')
			return (0); // Get them wildcards!
		p_char = ft_strchr(p_char + 1, '*');
	}
	/*
		- If the expanded wildcard contains different arguments, these are as 
		many tokens to add to the list.
		- If no expansion is possible, keep the original token.
	*/
	return (0);
}

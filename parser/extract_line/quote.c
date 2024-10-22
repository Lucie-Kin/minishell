/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 23:07:20 by libousse          #+#    #+#             */
/*   Updated: 2024/10/22 14:58:51 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

char	*find_unclosed_quote(const char *s)
{
	size_t	i;
	char	*quote;

	if (!s)
		return (0);
	i = 0;
	quote = 0;
	while (s[i])
	{
		if (is_char_start_of_quote(s, i, quote))
			quote = (char *)s + i;
		else if (is_char_end_of_quote(s, i, quote))
			quote = 0;
		++i;
	}
	return (quote);
}

int	is_char_start_of_quote(const char *s, size_t i, char *quote)
{
	if (quote)
		return (0);
	return ((s[i] == '"' || s[i] == '\'') && (!i || s[i - 1] != '\\'));
}

int	is_char_end_of_quote(const char *s, size_t i, char *quote)
{
	if (!i || !quote || *quote != s[i])
		return (0);
	return (s[i - 1] != '\\'
		|| (*quote == '\'' && !(quote > s && *(quote - 1) == '$')));
}

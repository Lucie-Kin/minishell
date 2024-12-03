/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_clean_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:50:54 by libousse          #+#    #+#             */
/*   Updated: 2024/12/03 23:30:12 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*handle_end_of_quote(char *parsed, size_t *i, char **quote,
				int *is_ansi_c_quote);
static void	remove_char(char *to_remove, size_t *index_to_decrement);
static int	is_backslash_to_remove(const char *s, char *quote,
				int *is_ansi_c_quote);
static void	remove_backslash(char *backslash, size_t *i, int next_is_newline);

/*
	Used in the parser and also meant for the env builtin:
	- Process ANSI-C quoting (`$'string'`) and localized string (`$"string"`).
	- Remove the backslash in escaped characters.
	- Remove the newline character if escaped and it's not in single quotes.
	- Remove external quotes.
*/
char	*get_clean_token(const char *s)
{
	size_t	i;
	int		is_ansi_c_quote;
	char	*parsed;
	char	*quote;

	parsed = ft_strdup(s);
	if (!parsed)
		return (0);
	i = 0;
	quote = 0;
	is_ansi_c_quote = 0;
	while (parsed[i])
	{
		if (!quote && (parsed[i] == '"' || parsed[i] == '\''))
			quote = parsed + i;
		else if (quote && *quote == parsed[i])
		{
			parsed = handle_end_of_quote(parsed, &i, &quote, &is_ansi_c_quote);
			quote = 0;
		}
		else if (is_backslash_to_remove(parsed + i, quote, &is_ansi_c_quote))
			remove_backslash(parsed + i, &i, parsed[i + 1] == '\n');
		++i;
	}
	return (parsed);
}

static char	*handle_end_of_quote(char *parsed, size_t *i, char **quote,
	int *is_ansi_c_quote)
{
	if (*is_ansi_c_quote)
		parsed = process_ansi_c_quoting(parsed, i, quote);
	*is_ansi_c_quote = 0;
	remove_char(*quote, i);
	remove_char(parsed + *i, i);
	return (parsed);
}

static void	remove_char(char *to_remove, size_t *index_to_decrement)
{
	ft_memmove(to_remove, to_remove + 1, ft_strlen(to_remove + 1) + 1);
	if (index_to_decrement)
		--*index_to_decrement;
	return ;
}

static int	is_backslash_to_remove(const char *s, char *quote,
			int *is_ansi_c_quote)
{
	if (s[0] == '$' && s[1] && (s[1] == '"' || s[1] == '\''))
		*is_ansi_c_quote = 1;
	if (s[0] == '\\' && s[1])
	{
		if (!quote)
			return (1);
		else if (*quote == '"' && (s[1] == '\n' || s[1] == '"' || s[1] == '$'
				|| s[1] == '\\' || s[1] == '`'))
			return (1);
	}
	return (0);
}

static void	remove_backslash(char *backslash, size_t *i, int next_is_newline)
{
	remove_char(backslash, 0);
	if (next_is_newline)
		remove_char(backslash, i);
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 23:07:20 by libousse          #+#    #+#             */
/*   Updated: 2024/10/24 18:56:44 by libousse         ###   ########.fr       */
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
	return ((s[i] == '"' || s[i] == '\'')
		&& !(count_char_before(s, i, '\\') % 2));
}

int	is_char_end_of_quote(const char *s, size_t i, char *quote)
{
	if (!i || !quote || *quote != s[i])
		return (0);
	return ((*quote == '\'' && !(quote > s && *(quote - 1) == '$'))
		|| !(count_char_before(s, i, '\\') % 2));
}

size_t	count_char_before(const char *s, size_t i, char c)
{
	size_t	amount;
	size_t	len;

	len = ft_strlen(s);
	if (i > len)
		i = len;
	amount = 0;
	while (i && s[--i] == c)
		++amount;
	return (amount);
}

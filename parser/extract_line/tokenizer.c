/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:13:12 by libousse          #+#    #+#             */
/*   Updated: 2024/10/31 18:04:25 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static char		*surround_metacharacters_with_spaces(char *s);
static char		*insert_spaces(char *s, size_t i);
static void		place_split_points(char *s, char split_val, int (*cmp)(int));

char	**tokenize(const char *s, int meta_space, int (*cmp)(int))
{
	char	**tokens;
	char	*dup;

	dup = ft_strdup(s);
	if (!dup)
		return (0);
	if (meta_space)
		dup = surround_metacharacters_with_spaces(dup);
	place_split_points(dup, SEP, cmp);
	tokens = ft_split(dup, SEP);
	free(dup);
	if (tokens && !tokens[0])
	{
		free(tokens);
		return (0);
	}
	return (tokens);
}

static char	*surround_metacharacters_with_spaces(char *s)
{
	size_t	i;
	char	*quote;

	i = 0;
	quote = 0;
	while (s[i])
	{
		if (!quote)
		{
			if (is_char_start_of_quote(s, i, quote))
				quote = s + i;
			else if (is_metacharacter(s[i]))
				s = insert_spaces(s, i);
		}
		else if (is_char_end_of_quote(s, i, quote))
			quote = 0;
		++i;
	}
	return (s);
}

static char	*insert_spaces(char *s, size_t i)
{
	char	*tmp;

	tmp = 0;
	if (i && !ft_isspace(s[i - 1]) && ((s[i - 1] != s[i] && s[i - 1] != '\\')
			|| s[i] == '(' || s[i] == ')' || count_char_before(s, i, s[i]) > 1))
		tmp = insert_str_before_char(s, i, " ");
	if (tmp)
	{
		free(s);
		s = tmp;
	}
	if (s[i + 1] && !ft_isspace(s[i + 1]) && s[i + 1] != s[i])
		tmp = insert_str_before_char(s, i + 1, " ");
	if (tmp)
	{
		free(s);
		s = tmp;
	}
	return (s);
}

static void	place_split_points(char *s, char split_val, int (*cmp)(int))
{
	size_t	i;
	char	*quote;

	i = 0;
	quote = 0;
	while (s[i])
	{
		if (!quote)
		{
			if (is_char_start_of_quote(s, i, quote))
				quote = s + i;
			else if (cmp(s[i]) && !(ft_isspace(s[i]) && i && s[i - 1] == '\\'))
				s[i] = split_val;
		}
		else if (is_char_end_of_quote(s, i, quote))
			quote = 0;
		++i;
	}
	return ;
}

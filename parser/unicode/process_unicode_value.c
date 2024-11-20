/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_unicode_value.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:47:46 by libousse          #+#    #+#             */
/*   Updated: 2024/11/16 11:45:39 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static char		*get_utf8_char(const char *unicode);
static void		four_byte_encoding(char *encoded, int codepoint);
static void		insert_unicode_value(char **s, size_t *i, char *encoded);
static size_t	get_unicode_format_length(const char *unicode);

void	process_unicode_value(int is_echo_e, char **s, size_t *i)
{
	char	*encoded;

	encoded = get_utf8_char(*s + *i);
	if (!encoded)
		return ;
	if (!encoded[0] && !is_echo_e)
	{
		(*s)[*i] = 0;
		free(encoded);
		return ;
	}
	insert_unicode_value(s, i, encoded);
	return ;
}

static char	*get_utf8_char(const char *unicode)
{
	char	*encoded;
	int		codepoint;

	codepoint = get_utf8_codepoint(unicode);
	if (codepoint < 0)
		return (0);
	encoded = ft_calloc(5, sizeof(char));
	if (!encoded)
		return (0);
	if (codepoint <= 0x7F)
		encoded[0] = codepoint;
	else if (codepoint <= 0x7FF)
	{
		encoded[0] = 0xC0 | ((codepoint >> 6) & 0x1F);
		encoded[1] = 0x80 | (codepoint & 0x3F);
	}
	else if (codepoint <= 0xFFFF)
	{
		encoded[0] = 0xE0 | ((codepoint >> 12) & 0x0F);
		encoded[1] = 0x80 | ((codepoint >> 6) & 0x3F);
		encoded[2] = 0x80 | (codepoint & 0x3F);
	}
	else if (codepoint <= 0x10FFFF)
		four_byte_encoding(encoded, codepoint);
	return (encoded);
}

static void	four_byte_encoding(char *encoded, int codepoint)
{
	encoded[0] = 0xF0 | ((codepoint >> 18) & 0x07);
	encoded[1] = 0x80 | ((codepoint >> 12) & 0x3F);
	encoded[2] = 0x80 | ((codepoint >> 6) & 0x3F);
	encoded[3] = 0x80 | (codepoint & 0x3F);
	return ;
}

static void	insert_unicode_value(char **s, size_t *i, char *encoded)
{
	char	*sub[2];
	size_t	len;

	len = get_unicode_format_length(*s + *i);
	ft_memmove(*s + *i, *s + *i + len + 1, ft_strlen(*s + *i + len + 1) + 1);
	sub[0] = ft_substr(*s, 0, *i);
	sub[1] = ft_substr(*s, *i, ft_strlen(*s + *i));
	*i += ft_strlen(encoded);
	free(*s);
	*s = ft_strjoin(sub[0], encoded);
	free(sub[0]);
	free(encoded);
	encoded = *s;
	*s = ft_strjoin(encoded, sub[1]);
	free(sub[1]);
	free(encoded);
	return ;
}

static size_t	get_unicode_format_length(const char *unicode)
{
	size_t	len;
	size_t	max_len;

	max_len = 4;
	if (unicode[0] == 'U')
		max_len = 8;
	len = 0;
	while (len < max_len && unicode[1 + len] && is_hex_digit(unicode[1 + len]))
		++len;
	return (len);
}

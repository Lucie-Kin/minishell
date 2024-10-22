/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_escaped_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:25:17 by libousse          #+#    #+#             */
/*   Updated: 2024/10/22 14:56:01 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static int	is_escaped_character(const char *s);
static void	replace_with_special_character(char *s);
static void	process_octal_value(char *s);
static void	process_hexadecimal_value(char *s);

/*
	This function is meant for the ANSI C quoting ($'string' notation), which 
	makes the parser escape special characters.

	Beware of "\c", which is not an actual ASCII character, and is to be 
	replaced with a control character. For example, "\cC" is to be replaced 
	with the ASCII character ETX (end of text) of dec value 3, or in other 
	words "Ctrl-C" in the terminal. Note that inserting this character in a 
	string doesn't send any signal, it's only interpreted when the Ctrl key is 
	pressed. Control characters can also be written in oct or hex format. All 
	of that to say that not only is "\c" superfluous, it also seems to have 
	undefined behavior when followed by a non-alpha character. For simplicity's 
	sake, it's replaced with '\0'.
*/

char	*get_escaped_token(const char *s)
{
	/*
		\uHHHH
		the Unicode (ISO/IEC 10646) char whose value is the hex value HHHH 
		(1 to 4 hex digits)

		\UHHHHHHHH
		the Unicode (ISO/IEC 10646) char whose value is the hex value HHHHHHHH 
		(1 to 8 hex digits)
	*/
	size_t	i;
	char	*parsed;

	parsed = ft_strdup(s);
	if (!parsed)
		return (0);
	i = 0;
	while (parsed[i])
	{
		if (is_escaped_character(parsed + i))
		{
			replace_with_special_character(parsed + i);
			if (!parsed[i])
				--i;
		}
		++i;
	}
	return (parsed);
}

static int	is_escaped_character(const char *s)
{
	if (s[0] == '\\')
	{
		if (s[1] == '\\' || s[1] == 'a' || s[1] == 'b' || s[1] == 'c'
			|| s[1] == 'e' || s[1] == 'E' || s[1] == 'f' || s[1] == 'n'
			|| s[1] == 'r' || s[1] == 't' || s[1] == 'v' || ft_isdigit(s[1])
			|| s[1] == 'x' || s[1] == '"' || s[1] == '\'' || s[1] == '?')
			return (1);
	}
	return (0);
}

static void	replace_with_special_character(char *s)
{
	ft_memmove(s, s + 1, ft_strlen(s + 1) + 1);
	if (s[0] == 'a')
		s[0] = '\a';
	else if (s[0] == 'b')
		s[0] = '\b';
	else if (s[0] == 'c')
		s[0] = '\0';
	else if (s[0] == 'e' || s[0] == 'E')
		s[0] = 27;
	else if (s[0] == 'f')
		s[0] = '\f';
	else if (s[0] == 'n')
		s[0] = '\n';
	else if (s[0] == 'r')
		s[0] = '\r';
	else if (s[0] == 't')
		s[0] = '\t';
	else if (s[0] == 'v')
		s[0] = '\v';
	else if (ft_isdigit(s[0]))
		process_octal_value(s);
	else if (s[0] == 'x')
		process_hexadecimal_value(s);
	return ;
}

static void	process_octal_value(char *s)
{
	int		i;
	char	arr[4];

	ft_bzero(arr, 4 * sizeof(char));
	i = 0;
	while (i < 3 && ft_isdigit(s[0]))
	{
		arr[i] = s[0];
		if (i < 2)
			ft_memmove(s, s + 1, ft_strlen(s + 1) + 1);
		++i;
	}
	s[0] = ft_atoi_base(arr, "01234567");
	return ;
}

static void	process_hexadecimal_value(char *s)
{
	int		i;
	char	arr[3];

	ft_bzero(arr, 3 * sizeof(char));
	i = 0;
	while (i < 2 && (ft_isdigit(s[1]) || (s[1] >= 'a' && s[1] <= 'f')
			|| (s[1] >= 'A' && s[1] <= 'F')))
	{
		arr[i] = ft_toupper(s[1]);
		ft_memmove(s + 1, s + 2, ft_strlen(s + 2) + 1);
		++i;
	}
	s[0] = ft_atoi_base(arr, "0123456789ABCDEF");
	return ;
}

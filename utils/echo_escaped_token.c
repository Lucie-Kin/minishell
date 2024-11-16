/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_escaped_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:59:58 by libousse          #+#    #+#             */
/*   Updated: 2024/11/16 11:44:08 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_escaped_character(const char *s);
static void	replace_with_special_character(char *s);
static void	process_octal_value(char *s);
static void	process_hexadecimal_value(char *s);

/*
	This function is meant for echo's -e option.

	Beware of "\c", which is not an actual ASCII character. It's replaced with 
	'\0' and also acts as the -n option.

	Also note that Unicode hex format is supported, despite the feature not 
	being specified in the man page of echo. This is because Bash' echo builtin 
	implements it, and we're mimicking this shell.
*/
char	*get_echo_escaped_token(const char *s, int *is_c_found)
{
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
			if (!parsed[i] && is_c_found)
				*is_c_found = 1;
			process_unicode_value(1, &parsed, &i);
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
			|| s[1] == 'r' || s[1] == 't' || s[1] == 'v' || s[1] == '0'
			|| s[1] == 'x' || is_unicode_format(s + 1))
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
	else if (s[0] == '0')
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
	while (i < 3 && ft_isdigit(s[1]))
	{
		arr[i] = s[1];
		ft_memmove(s + 1, s + 2, ft_strlen(s + 2) + 1);
		++i;
	}
	s[0] = ft_atoi_base(arr, "01234567");
	if (!s[0])
		ft_memmove(s, s + 1, ft_strlen(s + 1) + 1);
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
	if (!s[0])
		ft_memmove(s, s + 1, ft_strlen(s + 1) + 1);
	return ;
}

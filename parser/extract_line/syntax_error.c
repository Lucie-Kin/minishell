/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 22:33:41 by libousse          #+#    #+#             */
/*   Updated: 2024/10/27 22:34:30 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int	check_for_syntax_errors(const char *s)
{
	(void)s;
	/*
	size_t	i;

	// LEGAL: `echo a | (cd .. && ls)`
	// LEGAL: `(cd .. && ls) > out`
	// ILLEGAL: `< (cd .. && ls)` or `< main.c (cd .. && ls)`
	// LEGAL: `(cat) < main.c` or `(ls) < main.c`

	i = 0;
	while (tokens && tokens[i])
	{
		if (is_metacharacter(tokens[i][0]))
		{
			if (!i && (tokens[i][0] == ';' || tokens[i][0] == '|'
					|| tokens[i][0] == '&'))
				return (0);
			if (i && is_metacharacter(tokens[i - 1][0]))
			{
		*/
				/*
					( -> can be preceded by ';', '|' or '&'
					) -> can be preceded by ';'
					; -> can be preceded by ')' 
					| -> can be preceded by ')'
					& -> can be preceded by ')'
					< -> can be preceded by '(', ')', ';', '|' or '&'
					> -> can be preceded by '(', ')', ';', '|' or '&'
				*/
		/*
				if (tokens[i][0] == '(' && tokens[i - 1][0] != ';'
						&& tokens[i - 1][0] != '|' && tokens[i - 1][0] != '&')
					return (0);
				else if (tokens[i][0] == ')' && tokens[i - 1][0] != ';')
					return (0);
				else if ((tokens[i][0] == ';' || tokens[i][0] == '|'
						|| tokens[i][0] == '&') && tokens[i - 1][0] != ')')
					return (0);
				else if ((tokens[i][0] == '<' || tokens[i][0] == '>')
						&& (tokens[i - 1][0] == '<' || tokens[i - 1][0] == '>'))
					return (0);
			}
			if (tokens[i][0] == ';' && ft_strlen(tokens[i]) > 1)
				return (0);
			if (tokens[i][0] != '(' && tokens[i][0] != ')'
					&& ft_strlen(tokens[i]) > 2)
				return (0);
			if (tokens[i][0] == '<' || tokens[i][0] == '>')
			{
				if (!tokens[i + 1])
					return (0);
				else if (!ft_strcmp(tokens[i], "<<")
					&& !is_metacharacter(tokens[i + 1][0])
					&& !create_heredoc(sh, index, tokens[i + 1]))
						return (0);
			}
		}
		++i;
	}
	*/
	return (1);
}

	/*
		- It's easier to check for errors with tokens. Get all the heredoc 
		content you can before encountering the first error. Note that this 
		content is added to history.

		For example:

		$ cat << << EOF \
		bash: syntax error near unexpected token `<<'

		$ cat << EOF << << \
		bash: syntax error near unexpected token `<<'
		> hello
		> EOF
	*/
/*
	( ) ; | & < >

	- No left operand:

		$ ;
		bash: syntax error near unexpected token `;'
		$ |
		bash: syntax error near unexpected token `|'
		$ ||
		bash: syntax error near unexpected token `||'
		$ &&
		bash: syntax error near unexpected token `&&'
		$ < <
		bash: syntax error near unexpected token `<'
		$ < < a
		bash: syntax error near unexpected token `<'
		$ < |
		bash: syntax error near unexpected token `|'

	- Bad amount of characters in the special token:

		$ ls;;
		bash: syntax error near unexpected token `;;'
		$ a ||| b
		bash: syntax error near unexpected token `|'
		$ a &&& b
		bash: syntax error near unexpected token `&'
		$ a & b
		-> Not an error in Bash, but it's background jobs so draw a syntax 
		error anyway

	- Empty parentheses:

		$ ()
		bash: syntax error near unexpected token `)'
		$ ( )
		bash: syntax error near unexpected token `)'

		-> Note: Check at school what's written in history with `(` and then a 
		prompt of `)`.
	
	- Unclosed parentheses:

		$ )
		bash: syntax error near unexpected token `)'
		$ (a(
		bash: syntax error near unexpected token `newline'
	
		(((ls) && echo a) + )

		+1
		+1
		+1
		-1
		-1
		= 3 - 2 = 1

		((a)(

		2 - 1 + 1

		- Must not be negative.
		- Needs to be 0 before adding (= opening a parenthese).
*/

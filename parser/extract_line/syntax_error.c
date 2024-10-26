/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 22:04:54 by libousse          #+#    #+#             */
/*   Updated: 2024/10/26 22:26:45 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int	check_for_syntax_errors(const char *s)
{
	// TODO
	(void)s;
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
	return (1);
}

/*
	A comment starts at the first '#' if it's preceded by a whitespace (not 
	`ls\ #' but `ls #`).
	The comment is written to history.
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
*/

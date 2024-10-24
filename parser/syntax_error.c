/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 22:04:54 by libousse          #+#    #+#             */
/*   Updated: 2024/10/22 13:18:53 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_for_syntax_errors(const char *s)
{
	// TODO
	(void)s;
	return (1);
}

/*
	If command name is ".", exit code is 2 and msg is:
		"bash: .: filename argument required"
		".: usage: . filename [arguments]"


	- Search for syntax errors.
	- If any, output the error and still prompt for the heredocs placed before 
	the error and add them to history as well.

		$ cat << << EOF \
		bash: syntax error near unexpected token `<<'

		$ cat << EOF << << \
		bash: syntax error near unexpected token `<<'
		> hello
		> EOF

		$ ;
		bash: syntax error near unexpected token `;'
		$  ;
		bash: syntax error near unexpected token `;'
		$ .;
		-> error drawn by the executor for '.', because ';' is valid

		$ &&
		bash: syntax error near unexpected token `&&'
		$ |
		bash: syntax error near unexpected token `|'
		$ ||
		bash: syntax error near unexpected token `||'
		$ a &&& b
		bash: syntax error near unexpected token `&'
		$ a ||| b
		bash: syntax error near unexpected token `|'
		$ a & b
		-> Not an error in Bash, but it's background jobs so draw a syntax 
		error anyway

		$ )
		bash: syntax error near unexpected token `)'
		$ ()
		bash: syntax error near unexpected token `)'
		$ ( )
		bash: syntax error near unexpected token `)'
		$ (.)
		-> Executor error, so no syntax error here
		$ (a(
		bash: syntax error near unexpected token `newline'

		Draw a syntax error for backticks, because not implemented.

		Draw a syntax error for exclamations marks (history recall): don't 
		accept it in any argument other than within single quotes where it's 
		literal.

		The hashtag is a comment. Everything written a hashtag is written in 
		history but completely ignored.

		The tilde is always replaced with the home path when standing alone, 
		but is treated as a mere character in quotes or if next to another 
		character.

		Curly braces and square brackets are not always a feature, they can be 
		treated like mere characters sometimes. When?

		$ % & * + , - / : ; < = > ? @ ^ _
*/

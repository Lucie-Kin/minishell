/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 22:33:41 by libousse          #+#    #+#             */
/*   Updated: 2024/11/04 15:00:50 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static char	*get_syntax_err_msg(const char *tok);
static int	check_meta_token(char **tok, size_t i, char **err_msg);

// LEGAL: `echo a | (cd .. && ls)`
// LEGAL: `(cd .. && ls) > out`
// ILLEGAL: `< (cd .. && ls)` or `< main.c (cd .. && ls)`
// LEGAL: `(cat) < main.c` or `(ls) < main.c`

/*
	BASH

	$ cat << EOF << << \
	bash: syntax error near unexpected token `<<'
	> hello
	> EOF
	$ cat << EOF << << hello
	EOF
	[newline]

	MINISHELL

	$ cat << EOF << << \
	bigerrno: syntax error near unexpected token `<<'
	> hello
	> EOF
	$ cat << EOF << << \
	hello
	EOF
	[newline]
*/
/*
	BASH

	$ (
	> )
	bash: syntax error near unexpected token `)'
	$ ( )

	MINISHELL
	$ (
	> )
	$ (; )
*/

int	check_for_syntax_errors(t_sh* sh, size_t index)
{
	size_t	i;
	int		is_legal;
	char	**tokens;
	char	*err_msg;

	if (!sh->rl.arr[index])
		return (1);
	tokens = tokenize(sh->rl.arr[index]->value, 1, ft_isspace);
	if (!tokens)
		return (1);
	i = 0;
	is_legal = 1;
	while (is_legal && tokens[i])
	{
		if (is_metacharacter(tokens[i][0]))
			is_legal = check_meta_token(tokens, i, &err_msg);
		++i;
	}
	if (!is_legal)
	{
		sh->exit_code = 2;
		output_error(2, err_msg);
	}
	free_entire_array((void **)tokens, free);
	return (is_legal);
}

static char	*get_syntax_err_msg(const char *tok)
{
	char	*tmp1;
	char	*tmp2;

	if (!tok)
		tmp1 = compose_err_msg(SHELL, 0, 0,
			"syntax error near unexpected token `newline'");
	else
	{
		tmp1 = ft_strjoin("syntax error near unexpected token `", tok);
		tmp2 = ft_strjoin(tmp1, "'");
		free(tmp1);
		tmp1 = compose_err_msg(SHELL, 0, 0, tmp2);
		free(tmp2);
	}
	return (tmp1);
}

static int	check_meta_token(char **tok, size_t i, char **err_msg)
{
	// If no left operand
	if (!i && (tok[i][0] == ';' || tok[i][0] == '|' || tok[i][0] == '&'))
	{
		*err_msg = get_syntax_err_msg(tok[i]);
		return (0);
	}

	/*
	if (!ft_strcmp(tok[i], "<<") && tok[i + 1] && !ft_strcmp(tok[i + 1], "<<"))
	{
		*err_msg = compose_err_msg(SHELL, 0, 0,
				"syntax error near unexpected token `<<'");
		return (0);
	}
	*/
	return (1);
}


	/*
			if (!i && (tokens[i][0] == ';' || tokens[i][0] == '|'
					|| tokens[i][0] == '&'))
				return (0);
			if (i && is_metacharacter(tokens[i - 1][0]))
			{
				//	( -> can be preceded by ';', '|' or '&'
				//	) -> can be preceded by ';'
				//	; -> can be preceded by ')' 
				//	| -> can be preceded by ')'
				//	& -> can be preceded by ')'
				//	< -> can be preceded by '(', ')', ';', '|' or '&'
				//	> -> can be preceded by '(', ')', ';', '|' or '&'
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 22:33:41 by libousse          #+#    #+#             */
/*   Updated: 2024/12/03 23:29:01 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	check_meta_token(char **tok, size_t i, char **err_msg);
static int	err_on_curr(char **tok, size_t i);
static int	err_on_next(char **tok, size_t i);
static char	*get_syntax_err_msg(const char *tok);

int	check_for_syntax_errors(t_sh *sh, size_t index)
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

static int	check_meta_token(char **tok, size_t i, char **err_msg)
{
	if (err_on_curr(tok, i))
	{
		*err_msg = get_syntax_err_msg(tok[i]);
		return (0);
	}
	else if (err_on_next(tok, i))
	{
		*err_msg = get_syntax_err_msg(tok[i + 1]);
		return (0);
	}
	return (1);
}

/*
	If no left operand (command can start with '(', '<', '>')
	If '(' doesn't start the command and is preceded with non-meta
	If bad token length
	If ')' but no prior '('
*/
static int	err_on_curr(char **tok, size_t i)
{
	size_t	j;

	if (!i && tok[i][0] != '(' && tok[i][0] != '<' && tok[i][0] != '>')
		return (1);
	else if (i && tok[i][0] == '(' && !is_metacharacter(tok[i - 1][0]))
		return (1);
	else if ((tok[i][0] == '&' && !tok[i][1])
		|| (tok[i][0] == ';' && tok[i][1]))
		return (1);
	else if (tok[i][0] == ')')
	{
		j = i;
		while (j > 0 && tok[j][0] != '(')
			--j;
		return (tok[j][0] != '(');
	}
	return (0);
}

/* If next token is unexpected */
static int	err_on_next(char **tok, size_t i)
{
	if (tok[i][0] == ')' && tok[i + 1] && (tok[i + 1][0] == '('
		|| !is_metacharacter(tok[i + 1][0])))
		return (1);
	else if (tok[i][0] == ';' && tok[i + 1] && (tok[i + 1][0] == ';'
		|| tok[i + 1][0] == '|' || tok[i + 1][0] == '&'))
		return (1);
	else if ((tok[i][0] == '(' || tok[i][0] == '|' || tok[i][0] == '&')
		&& tok[i + 1] && (tok[i + 1][0] == ')' || tok[i + 1][0] == ';'
		|| tok[i + 1][0] == '|' || tok[i + 1][0] == '&'))
		return (1);
	else if ((tok[i][0] == '<' || tok[i][0] == '>')
		&& (!tok[i + 1] || is_metacharacter(tok[i + 1][0])))
		return (1);
	return (0);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_right_operand_and_parentheses.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:31:51 by libousse          #+#    #+#             */
/*   Updated: 2024/10/15 14:42:05 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	no_right_operand_missing(char **cmdl_tokens);
static int	are_all_parentheses_closed(char **cmdl_tokens, char **prefix,
				t_rl_arr **arr, size_t arr_len);
static int	increment_nbr_parentheses(const char *s);

int	check_right_operand_and_parentheses(t_sh *sh, char **prefix)
{
	int		is_input_complete;
	char	*cmdl;
	char	**cmdl_tokens;

	is_input_complete = 1;
	cmdl = concatenate_all_cmdl_lines(sh);
	if (!cmdl)
		return (is_input_complete);
	cmdl_tokens = tokenize(cmdl, 1, ft_isspace);
	free(cmdl);
	if (!cmdl_tokens)
		return (is_input_complete);
	is_input_complete = no_right_operand_missing(cmdl_tokens);
	if (!is_input_complete)
		*prefix = " ";
	else
		is_input_complete = are_all_parentheses_closed(cmdl_tokens, prefix,
				sh->rl.arr, get_array_length((void **)sh->rl.arr));
	free_entire_array((void **)cmdl_tokens, free);
	return (is_input_complete);
}

static int	no_right_operand_missing(char **cmdl_tokens)
{
	char	*p_last_token;

	if (cmdl_tokens)
	{
		p_last_token = cmdl_tokens[get_array_length((void **)cmdl_tokens) - 1];
		if (!ft_strcmp(p_last_token, "|") || !ft_strcmp(p_last_token, "||")
			|| !ft_strcmp(p_last_token, "&&"))
			return (0);
	}
	return (1);
}

static int	are_all_parentheses_closed(char **cmdl_tokens, char **prefix,
	t_rl_arr **rl_arr, size_t rl_arr_len)
{
	size_t	i;
	size_t	j;
	int		nbr_parentheses;

	if (!cmdl_tokens)
		return (1);
	nbr_parentheses = 0;
	i = 0;
	while (cmdl_tokens[i])
		nbr_parentheses += increment_nbr_parentheses(cmdl_tokens[i++]);
	if (!nbr_parentheses)
		return (1);
	if (rl_arr && rl_arr_len && rl_arr[rl_arr_len - 1]->is_heredoc)
		*prefix = " ";
	else
	{
		*prefix = "; ";
		j = ft_strlen(cmdl_tokens[i - 1]) - 1;
		while (j && ft_isspace(cmdl_tokens[i - 1][j]))
			--j;
		if (cmdl_tokens[i - 1][j] == ';')
			*prefix = " ";
	}
	return (0);
}

static int	increment_nbr_parentheses(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] == '(')
		++i;
	if (!s[i])
		return (i);
	while (s[i] == ')')
		++i;
	if (!s[i])
		return (-i);
	return (0);
}

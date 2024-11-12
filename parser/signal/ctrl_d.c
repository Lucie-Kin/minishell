/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:55:57 by libousse          #+#    #+#             */
/*   Updated: 2024/11/12 14:10:38 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static void	check_cases(t_sh *sh, int *is_legal);
static int	case_unclosed_quote(t_sh *sh, int *is_legal, size_t arr_len);
static int	case_odd_amount_of_backslashes(t_sh *sh, size_t arr_len);
static int	case_missing_right_operand(t_sh *sh, int *is_legal);

void	handle_ctrl_d(t_sh *sh, int *is_legal)
{
	if (is_legal && !*is_legal)
	{
		sh->keep_running = 0;
		return ;
	}
	check_cases(sh, is_legal);
	if (!sh->keep_running && sh->level == 0)
		ft_putstr_fd("exit\n", 1);
	return ;
}

static void	check_cases(t_sh *sh, int *is_legal)
{
	size_t	arr_len;
	int		backslash;

	sh->keep_running = 0;
	if (!sh->rl.arr)
		return ;
	arr_len = get_array_length((void **)sh->rl.arr);
	if (sh->rl.arr[arr_len - 1]->is_heredoc)
		return ;
	if (case_unclosed_quote(sh, is_legal, arr_len))
		return ;
	backslash = case_odd_amount_of_backslashes(sh, arr_len);
	if (case_missing_right_operand(sh, is_legal))
		return ;
	if (backslash)
		++sh->level;
	else if (is_legal)
		*is_legal = 0;
	return ;
}

static int	case_unclosed_quote(t_sh *sh, int *is_legal, size_t arr_len)
{
	char	*p_quote;
	char	*msg;

	p_quote = find_unclosed_quote(sh->rl.arr[arr_len - 1]->value);
	if (!p_quote)
		return (0);
	msg = ft_strdup("unexpected EOF while looking for matching ` '");
	if (msg)
	{
		msg[ft_strlen(msg) - 2] = *p_quote;
		output_error(2, compose_err_msg(SHELL, 0, 0, msg));
		free(msg);
	}
	sh->exit_code = output_error(2, compose_err_msg(SHELL, 0, "syntax error",
				"unexpected end of file"));
	sh->keep_running = 1;
	if (is_legal)
		*is_legal = 0;
	return (1);
}

static int	case_odd_amount_of_backslashes(t_sh *sh, size_t arr_len)
{
	size_t	len;

	len = ft_strlen(sh->rl.arr[arr_len - 1]->value);
	if (!len)
		return (0);
	if (!(count_char_before(sh->rl.arr[arr_len - 1]->value, len, '\\')) % 2)
		return (0);
	sh->rl.arr[arr_len - 1]->value[len - 1] = 0;
	return (1);
}

static int	case_missing_right_operand(t_sh *sh, int *is_legal)
{
	if (check_right_operand_and_parentheses(sh, 0))
		return (0);
	sh->exit_code = output_error(2, compose_err_msg(SHELL, 0, "syntax error",
				"unexpected end of file"));
	if (is_legal)
		*is_legal = 0;
	return (1);
}

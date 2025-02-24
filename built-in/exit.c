/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:12:05 by lchauffo          #+#    #+#             */
/*   Updated: 2025/02/24 19:02:36 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigerrno.h"

/*
List of exit tests: 
exit
exit 42
exit 4a
exit aa
exit "   42   "
exit "  4  2"
exit "  4a"
exit "  a  "
exit 9223372036854775807
exit 9223372036854775808
exit -9223372036854775808
exit -9223372036854775809
exit -1

nm minishell | grep "U "
*/

static long	ft_pow(const int factor, int exponent);
static int	parse_exit_arg(char **arg, int *i, int *digits, int *sign);

#define MAX "9223372036854775807"
#define MIN "9223372036854775808"

int	bigerrno_exit(t_sh *sh, char **arg)
{
	long long	numb;
	int			i;
	int			sign;
	int			digits;

	sh->keep_running = FALSE;
	if (sh->subshell == 0)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (get_array_length((void **)arg) > 2)
		return (output_error(EPERM, compose_err_msg
				(SHELL, arg[0], NULL, ERR_NB_ARGS)));
	if (arg[1])
	{
		numb = 0;
		i = 0;
		digits = 0;
		sign = 1;
		parse_exit_arg(arg, &i, &digits, &sign);
		while (arg[1][i] && digits-- > 0)
			numb += (arg[1][i++] - '0') * ft_pow(10, digits);
		numb *= sign;
		return (numb % 256);
	}
	return (sh->exit_code);
}

static long	ft_pow(const int factor, int exponent)
{
	if (exponent == 0)
		return (1);
	return (factor * ft_pow(factor, --exponent));
}

static int	parse_exit_arg(char **arg, int *i, int *digits, int *sign)
{
	int			result;
	int			j;

	while (ft_isspace(arg[1][*i]))
		(*i)++;
	if (arg[1][(*i)] == '-')
		*sign = ((*i)++) % 1 - 1;
	while (ft_isdigit(arg[1][(*i) + (*digits)]))
		(*digits)++;
	j = (*i) + (*digits) - 1;
	while (arg[1][++j])
	{
		if (ft_isspace(arg[1][j]) == 0)
			return (output_error(ENOENT, compose_err_msg
					(SHELL, arg[0], arg[1], ERR_NONUM)));
	}
	result = ft_strncmp(arg[1] + (*i), MAX, ft_strlen(MAX));
	if (*sign == -1)
		result = ft_strncmp(arg[1] + (*i), MIN, ft_strlen(MIN));
	if (*digits > 19 || *digits == 0 || (*digits == 19 && result > 0))
		return (output_error(ENOENT, compose_err_msg
				(SHELL, arg[0], arg[1], ERR_NONUM)));
	return (0);
}

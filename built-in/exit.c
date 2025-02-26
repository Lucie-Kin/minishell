/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:12:05 by lchauffo          #+#    #+#             */
/*   Updated: 2025/02/26 19:39:47 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigerrno.h"

static int	parse_exit_arg(char **arg);
static int	extract_exit_nbr(const char *arg, int *start, int *len, int *sign);

/*
	List of exit tests: 
	exit
	exit 42
	exit 42 a
	exit 4a
	exit aa
	exit ""
	exit "   42   "
	exit "  4  2"
	exit "  4a"
	exit "  a  "
	exit 9223372036854775807
	exit 9223372036854775808
	exit -9223372036854775808
	exit -9223372036854775809
	exit -1

	Exit code is EPERM if too many args
	Exit code is ENOENT for any other error
*/

int	bigerrno_exit(t_sh *sh, char **arg)
{
	sh->keep_running = 0;
	if (sh->subshell == 0)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (!arg[1])
		return (sh->exit_code);
	if (get_array_length((void **)arg) > 2)
		return (output_error(EPERM,
				compose_err_msg(SHELL, arg[0], NULL, ERR_NB_ARGS)));
	return (parse_exit_arg(arg));
}

static int	parse_exit_arg(char **arg)
{
	long long	nbr;
	int			nbr_sign;
	int			nbr_start;
	int			nbr_len;

	nbr = 0;
	nbr_sign = 1;
	nbr_start = 0;
	nbr_len = 0;
	if (!extract_exit_nbr(arg[1], &nbr_start, &nbr_len, &nbr_sign))
		return (output_error(ENOENT,
				compose_err_msg(SHELL, arg[0], arg[1], ERR_NONUM)));
	while (arg[1][nbr_start] && nbr_len-- > 0)
		nbr += (arg[1][nbr_start++] - '0') * ft_pow(10, nbr_len);
	return (nbr * nbr_sign % 256);
}

static int	extract_exit_nbr(const char *arg, int *start, int *len, int *sign)
{
	int		i;
	char	*limit;

	while (ft_isspace(arg[*start]))
		++*start;
	if (arg[*start] == '-')
		*sign = ++*start % 1 - 1;
	while (ft_isdigit(arg[*start + *len]))
		++*len;
	i = *start + *len - 1;
	while (arg[++i])
	{
		if (!ft_isspace(arg[i]))
			return (0);
	}
	limit = "9223372036854775807";
	if (*sign == -1)
		limit = "9223372036854775808";
	return (!(*len == 0 || *len > 19 || (*len == 19
				&& ft_strncmp(arg + *start, limit, ft_strlen(limit)) > 0)));
}

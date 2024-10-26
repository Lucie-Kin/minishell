/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:14:06 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/25 13:20:33 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
void	bigerrno_echo(char **arg)
{
	size_t	i;
	int		opt_n;
	int		opt_e;

	i = 1;
	opt_n = 0;
	opt_e = 0;
	while (arg[i] && arg[i][0] == '-')
	{
		if (ft_strchr(&arg[i][1], 'n'))
			opt_n = 1;
		if (ft_strchr(&arg[i][1], 'e'))
			opt_e = 1;
		++i;
	}
	while (arg[i])
	{
		if (!opt_e)
			ft_putstr_fd(arg[i], 1);
		else
		{
			char	*escaped;
			int		is_c_found;
			escaped = get_echo_escaped_token(arg[i], &is_c_found);
			if (escaped)
			{
				ft_putstr_fd(escaped, 1);
				free(escaped);
				if (is_c_found)
					opt_n = 1;
			}
		}
		if (arg[i + 1])
			ft_putstr_fd(" ", 1);
		++i;
	}
	if (!opt_n)
		ft_putstr_fd("\n", 1);
	return ;
}
*/

void	echo_option(char **arg, int *skip_newline, int *with_backlash,
		int *count)
{
	*skip_newline = FALSE;
	*with_backlash = FALSE;
	*count = 1;
	while (arg[*count] && arg[*count][0] == '-'
		&& (bn_countiter(&arg[*count][1], 'n') > 0
		|| bn_countiter(&arg[*count][1], 'e') > 0))
	{
		if (arg[*skip_newline][1] == 'n')
			*skip_newline = 2;
		else if (arg[*skip_newline][1] == 'e')
			(*with_backlash)++;
		(*count)++;
	}
}

void	bigerrno_echo(char **arg)
{
	int		to_be_echoed;
	int		skip_nl;
	int		with_backlash;
	int		count;
	char	*parsed;

	echo_option(arg, &skip_nl, &with_backlash, &count);
	to_be_echoed = count;
	while (arg[to_be_echoed])
	{
		if (to_be_echoed != count)
			write(1, " ", 1);
		if (with_backlash > 0)
		{
			parsed = get_echo_escaped_token(arg[to_be_echoed], &skip_nl);
			write(1, parsed, ft_strlen(parsed));
			free(parsed);
			if (skip_nl == 1)
				break ;
		}
		else
			write(1, arg[to_be_echoed], ft_strlen(arg[to_be_echoed]));
		to_be_echoed++;
	}
	if (skip_nl == FALSE)
		write(1, "\n", 1);
}

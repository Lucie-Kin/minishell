/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:14:06 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/21 18:56:21 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_option(char **arg, int *skip_newline, int *with_backlash,
		int *count)
{
	*skip_newline = 0;
	*with_backlash = 0;
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
			if (skip_nl == 1)
				break ;
		}
		else
			write(1, arg[to_be_echoed], ft_strlen(arg[to_be_echoed]));
		to_be_echoed++;
	}
	if (skip_nl == 0)
		write(1, "\n", 1);
}

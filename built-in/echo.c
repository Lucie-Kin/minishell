/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:14:06 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/07 12:32:21 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//Add char	*get_escaped_token(const char *s, int *is_c_found)

void	echo_option(char **arg, int *skip_newline, int *with_backlash,
		int *count)
{
	*skip_newline = 0;
	*with_backlash = 0;
	*count = 1;
	while (arg[*count] && arg[*count][0] == '-'
		&& (ft_iter(&arg[*count][1], 'n') == TRUE
		|| ft_iter(&arg[*count][1], 'e') == TRUE))
	{
		if (arg[*skip_newline][1] == 'n')
			*skip_newline = 2;
		else if (arg[*skip_newline][1] == 'e')
			*with_backlash++;
		*count++;
	}
}

void	bigerrno_echo(char **arg, int echo)
{
	int		to_be_echoed;
	int		skip_newline;
	int		with_backlash;
	int		count;
	char	*parsed;

	echo_option(arg + echo, skip_newline, with_backlash, count);
	to_be_echoed = echo + count;
	while (arg[to_be_echoed])
	{
		if (to_be_echoed != echo + count)
			write(1, " ", 1);
		if (with_backlash > 0)
		{
			parsed = get_escaped_token(arg[to_be_echoed], &skip_newline);
			write(1, parsed, ft_strlen(parsed));
			if (skip_newline == 1)
				break ;
		}
		else
			write(1, arg[to_be_echoed], ft_strlen(arg[to_be_echoed]));
		to_be_echoed++;
	}
	if (skip_newline == 0)
		write(1, "\n", 1);
}

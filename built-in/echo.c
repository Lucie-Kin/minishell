/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:14:06 by lchauffo          #+#    #+#             */
/*   Updated: 2024/11/22 14:50:59 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo_option(char **arg, int *skip_newline, int *with_backlash,
		int *count)
{
	int	i;

	*skip_newline = FALSE;
	*with_backlash = FALSE;
	*count = 1;
	while (arg[*count] && arg[*count][0] == '-' && arg[*count][1])
	{
		i = 1;
		while (arg[*count][i] && (arg[*count][i] == 'n'
			|| arg[*count][i] == 'e'))
			i++;
		if (arg[*count][i] != '\0')
			break ;
		if (ft_strchr(arg[*count], 'n'))
			*skip_newline = TRUE;
		if (ft_strchr(arg[*count], 'e'))
			*with_backlash = TRUE;
		(*count)++;
	}
	return (*count);
}

int	bigerrno_echo(char **arg)
{
	int		to_be_echoed;
	int		skip_nl;
	int		with_backlash;
	int		count;
	char	*parsed;

	to_be_echoed = echo_option(arg, &skip_nl, &with_backlash, &count) - 1;
	while (arg[++to_be_echoed])
	{
		if (to_be_echoed != count)
			write(1, " ", 1);
		if (with_backlash > 0)
		{
			parsed = get_echo_escaped_token(arg[to_be_echoed], &skip_nl);
			write(1, parsed, ft_strlen(parsed));
			free(parsed);
		}
		else
			write(1, arg[to_be_echoed], ft_strlen(arg[to_be_echoed]));
	}
	if (skip_nl == FALSE)
		write(1, "\n", 1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:14:06 by lchauffo          #+#    #+#             */
/*   Updated: 2024/12/06 20:14:20 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	echo_option(char **arg, int *skip_newline, int *with_backlash,
				int *count);

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
			ft_putstr_fd(" ", STDOUT_FILENO);
		if (with_backlash > 0)
		{
			parsed = get_echo_escaped_token(arg[to_be_echoed], &skip_nl);
			ft_putstr_fd(parsed, STDOUT_FILENO);
			free(parsed);
		}
		else
			ft_putstr_fd(arg[to_be_echoed], STDOUT_FILENO);
	}
	if (skip_nl == FALSE)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

static int	echo_option(char **arg, int *skip_newline, int *with_backlash,
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

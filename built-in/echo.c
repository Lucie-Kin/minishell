/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:14:06 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/02 17:11:22 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	bigerrno_echo(char **arg, int echo)
{
	int	to_be_echoed;
	int	skip_newline;

	skip_newline = 1;
	while (arg[echo + skip_newline] && arg[echo + skip_newline][0] == '-'
		&& ft_iter(&arg[echo + skip_newline][1], 'n') == TRUE)
		skip_newline++;
	to_be_echoed = echo + skip_newline;
	while (arg[to_be_echoed])
	{
		if (to_be_echoed != echo + skip_newline)
			write(1, " ", 1);
		write(1, arg[to_be_echoed], ft_strlen(arg[to_be_echoed]));
		to_be_echoed++;
	}
	if (skip_newline == 1)
		write(1, "\n", 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:10:36 by libousse          #+#    #+#             */
/*   Updated: 2024/09/17 17:24:57 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*compose_err_msg(char *cmd, char *arg, char *msg)
{
	char	*str1;
	char	*str2;

	if (cmd && arg)
	{
		str1 = ft_strjoin(cmd, ": ");
		str2 = ft_strjoin(str1, arg);
		free(str1);
		str1 = ft_strjoin(str2, ": ");
		free(str2);
	}
	else if (!arg)
		str1 = ft_strjoin(cmd, ": ");
	else
		str1 = ft_strjoin(arg, ": ");
	if (!str1)
		str2 = ft_strdup(msg);
	else
		str2 = ft_strjoin(str1, msg);
	free(str1);
	return (str2);
}

int	output_error(t_pl *pl)
{
	if (pl->exit_code)
	{
		ft_putstr_fd(pl->err_msg, 2);
		ft_putstr_fd("\n", 2);
		free(pl->err_msg);
		pl->err_msg = 0;
	}
	return (pl->exit_code);
}

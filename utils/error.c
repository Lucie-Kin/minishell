/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:10:36 by libousse          #+#    #+#             */
/*   Updated: 2024/10/26 17:23:35 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*compose_err_msg(const char *cmd, const char *arg, const char *msg)
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
	str1 = ft_strjoin(str2, "\n");
	free(str2);
	str2 = ft_strjoin("bigerrno: ", str1);
	free(str1);
	return (str2);
}

int	output_error(int code, char *msg)
{
	if (code)
	{
		ft_putstr_fd(msg, 2);
		free(msg);
	}
	return (code);
}

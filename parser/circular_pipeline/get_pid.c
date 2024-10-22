/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 11:55:43 by libousse          #+#    #+#             */
/*   Updated: 2024/10/13 14:40:44 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_pid(const char *first_arg)
{
	int		pid;
	char	*tmp1;
	char	*tmp2;

	if (!first_arg)
		return (0);
	tmp1 = ft_strjoin("ps aux | grep ", first_arg);
	tmp2 = ft_strjoin(tmp1, " | grep -v grep | awk '{print $2}' | tail -n 1");
	free(tmp1);
	if (!tmp2)
		return (0);
	// Circular pipeline to receive the number
	free(tmp2);
	pid = 12345;
	return (pid);
}

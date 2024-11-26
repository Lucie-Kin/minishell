/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:21:10 by lchauffo          #+#    #+#             */
/*   Updated: 2024/11/25 14:18:39 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	bigerrno_hidden(t_env **hidden, char **arg)
{
	if (arg[0] && !arg[1])
	{
		if (!hidden && !*hidden)
			perror("Nothing_to_print");
		else
			print_in_p_order(hidden, NULL);
	}
	else
	{
		output_error(EPERM, compose_err_msg(SHELL, "hidden", arg[1],
				strerror(E2BIG)));
		return (EPERM);
	}
	return (0);
}

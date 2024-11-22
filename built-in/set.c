/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:21:10 by lchauffo          #+#    #+#             */
/*   Updated: 2024/11/22 16:25:12 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	bigerrno_hidden(t_env **hidden, char **arg)
{
	if (!arg[1])
		print_in_p_order(hidden, NULL);
	else if (arg[1])
	{
		output_error(EPERM, compose_err_msg(SHELL, "hidden", arg[1],
				strerror(E2BIG)));
		return (EPERM);
	}
	return (0);
}

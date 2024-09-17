/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:02:55 by libousse          #+#    #+#             */
/*   Updated: 2024/09/17 17:47:23 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_file(t_pl *pl, char *file, int mode, int catch_err)
{
	if (mode == W_OK && access(file, F_OK) < 0)
	{
		errno = 0;
		return (1);
	}
	else if (access(file, mode) < 0)
	{
		if (catch_err)
		{
			pl->exit_code = errno;
			pl->err_msg = compose_err_msg(SHELL_NAME, file,
					strerror(pl->exit_code));
			if (pl->exit_code == EACCES)
				pl->exit_code = EPERM;
		}
		return (0);
	}
	return (1);
}

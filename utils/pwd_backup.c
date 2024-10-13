/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_backup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:05:17 by libousse          #+#    #+#             */
/*   Updated: 2024/09/21 12:07:39 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pwd_backup(t_sh *sh, const char *value)
{
	if (value)
	{
		free(sh->pwd_backup);
		sh->pwd_backup = ft_strdup(value);
	}
	return ;
}

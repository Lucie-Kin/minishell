/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlink_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:12:07 by libousse          #+#    #+#             */
/*   Updated: 2024/12/03 23:29:50 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	unlink_heredocs(t_sh *sh)
{
	size_t	i;

	if (!sh->rl.hd)
		return ;
	i = 0;
	while (sh->rl.hd[i])
	{
		unlink(sh->rl.hd[i]);
		++i;
	}
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:17:00 by lchauffo          #+#    #+#             */
/*   Updated: 2024/11/30 21:17:03 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	bigerrno_bonus(t_sh *sh, char **cmdl, int *code_err)
{
	if (ft_strcmp(cmdl[0], "lulu") == 0)
		*code_err = bigerrno_lulu(&sh->color);
	else if (ft_strcmp(cmdl[0], "shoot") == 0)
		*code_err = bigerrno_shoot(&sh->color, cmdl);
}
	// else if (ft_strcmp(cmdl[0], "hidden") == 0)
	// 	code_err = bigerrno_hidden(&sh->hidden, cmdl);

int	bigerrno_lulu(enum e_color *color)
{
	++(*color);
	if (*color >= E_DEFAULT)
		*color = 0;
	set_bg_color(color);
	return (0);
}

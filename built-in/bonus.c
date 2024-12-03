/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:17:00 by lchauffo          #+#    #+#             */
/*   Updated: 2024/12/03 20:25:52 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	bigerrno_disco(enum e_color *color)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		while ("DISCO YAY")
			bigerrno_lulu(color);
	}
	return (0);
}

int	bigerrno_lulu(enum e_color *color)
{
	++(*color);
	if (*color >= E_DEFAULT)
		*color = 0;
	set_bg_color(color);
	return (0);
}

void	bigerrno_bonus(t_sh *sh, char **cmdl, int *code_err)
{
	if (ft_strcmp(cmdl[0], "lulu") == 0)
		*code_err = bigerrno_lulu(&sh->color);
	else if (ft_strcmp(cmdl[0], "disco") == 0)
		*code_err = bigerrno_disco(&sh->color);
	else if (ft_strcmp(cmdl[0], "shoot") == 0)
		*code_err = bigerrno_shoot(sh, &sh->color, cmdl);
	else if (ft_strcmp(cmdl[0], "matrix") == 0)
	{
		*code_err = bigerrno_matrix(sh, &sh->color, cmdl);
	}
}
	// else if (ft_strcmp(cmdl[0], "hidden") == 0)
	// 	code_err = bigerrno_hidden(&sh->hidden, cmdl);

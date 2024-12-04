/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lulu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:38:43 by libousse          #+#    #+#             */
/*   Updated: 2024/12/04 18:03:17 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	match_prompt_color(t_sh *sh, char *color);

int	bigerrno_lulu(t_sh *sh, enum e_color *color)
{
	++(*color);
	if (*color >= E_DEFAULT)
		*color = 0;
	if (*color == E_GNOME)
	{
		sh->prompt_color1 = PRPT_COL_GRN;
		sh->prompt_color2 = PRPT_COL_BLU;
	}
	else if (*color == E_PEACH)
		match_prompt_color(sh, PRPT_COL_ORG);
	else if (*color == E_POWDER)
		match_prompt_color(sh, PRPT_COL_BLU);
	else if (*color == E_AZUL)
		match_prompt_color(sh, PRPT_COL_DBL);
	else if (*color == E_PURPLE)
		match_prompt_color(sh, PRPT_COL_LPP);
	else if (*color == E_PINK)
		match_prompt_color(sh, PRPT_COL_MAG);
	set_background_color(*color);
	return (0);
}

int	bigerrno_disco(t_sh *sh, enum e_color *color)
{
	int	pid[2];

	if (sh->pid_disco)
		kill(sh->pid_disco, SIGKILL);
	sh->pid_disco = fork();
	pid[0] = sh->pid_disco;
	pid[1] = 0;
	if (sh->pid_disco == 0)
	{
		while ("DISCO YAY" && !g_signum)
			bigerrno_lulu(sh, color);
		destroy_all_ex(sh);
		free_shell(sh);
		exit(418);
	}
	wait_for_subprocesses(sh, pid, WNOHANG);
	return (sh->ex->pl.exit_code);
}

static void	match_prompt_color(t_sh *sh, char *color)
{
	sh->prompt_color1 = color;
	sh->prompt_color2 = color;
}

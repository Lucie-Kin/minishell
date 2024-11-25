/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_cleaning.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:51:35 by libousse          #+#    #+#             */
/*   Updated: 2024/11/25 16:52:58 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static void	clean_pl_cmdl_tokens(t_pl *pl);
static void	tmp_clean_token(t_pl *pl, size_t i, size_t j);
static void	clean_pl_inf_tokens(t_pl *pl);
static void	clean_pl_outf_tokens(t_pl *pl);

void	clean_pl_tokens(t_pl *pl)
{
	if (!pl || !pl->cmdl || !pl->inf || !pl->outf)
		return ;
	clean_pl_cmdl_tokens(pl);
	clean_pl_inf_tokens(pl);
	clean_pl_outf_tokens(pl);
	return ;
}

static void	clean_pl_cmdl_tokens(t_pl *pl)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (pl->cmdl[i])
	{
		j = 0;
		while (pl->cmdl[i][j])
		{
			tmp_clean_token(pl, i, j);
			++j;
		}
		++i;
	}
	return ;
}

/*
	Temporary function to circumvent `\( a \)` becoming `( a )` and triggering 
	a subshell. This wouldn't be an issue if tokens were labeled instead of 
	remaining mere strings.
*/
static void	tmp_clean_token(t_pl *pl, size_t i, size_t j)
{
	char	*tmp;

	if (!ft_strcmp(pl->cmdl[i][j], "(") || !ft_strcmp(pl->cmdl[i][j], ")"))
		pl->cmdl[i][j][0] = SEP;
	else
	{
		tmp = get_clean_token(pl->cmdl[i][j]);
		if (tmp)
		{
			free(pl->cmdl[i][j]);
			pl->cmdl[i][j] = tmp;
		}
	}
	return ;
}

static void	clean_pl_inf_tokens(t_pl *pl)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 0;
	while (pl->inf[i])
	{
		j = 0;
		while (pl->inf[i][j])
		{
			tmp = get_clean_token(pl->inf[i][j]);
			if (tmp)
			{
				free(pl->inf[i][j]);
				pl->inf[i][j] = tmp;
			}
			++j;
		}
		++i;
	}
	return ;
}

static void	clean_pl_outf_tokens(t_pl *pl)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 0;
	while (pl->outf[i])
	{
		j = 0;
		while (pl->outf[i][j].filename)
		{
			tmp = get_clean_token(pl->outf[i][j].filename);
			if (tmp)
			{
				free(pl->outf[i][j].filename);
				pl->outf[i][j].filename = tmp;
			}
			++j;
		}
		++i;
	}
	return ;
}

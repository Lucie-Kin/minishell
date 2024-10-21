/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_inf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:39:10 by libousse          #+#    #+#             */
/*   Updated: 2024/10/18 23:25:04 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	inner_loop(char ***inf, char ***cmdl, size_t i, char **hd_dup);
static void	extract_name(char ***curr_inf, char **curr_src, size_t j, size_t k);

char	***get_pl_inf(t_pl *pl, char **hd_dup)
{
	size_t	i;
	char	***inf;

	inf = ft_calloc(pl->len + 1, sizeof(char **));
	if (!inf)
		return (0);
	i = 0;
	while (pl->cmdl[i])
	{
		if (!inner_loop(inf, pl->cmdl, i, hd_dup))
		{
			destroy_pl_inf(inf);
			inf = 0;
			break ;
		}
		++i;
	}
	free_entire_array((void **)hd_dup, free);
	return (inf);
}

void	*destroy_pl_inf(char ***inf)
{
	size_t	i;

	if (!inf)
		return (0);
	i = 0;
	while (inf[i])
	{
		free_entire_array((void **)inf[i], free);
		++i;
	}
	free(inf);
	return (0);
}

static int	inner_loop(char ***inf, char ***cmdl, size_t i, char **hd_dup)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	while (cmdl[i][j])
	{
		if (!ft_strcmp(cmdl[i][j], "<"))
		{
			remove_array_elements((void **)cmdl[i], j, j, free);
			extract_name(inf + i, cmdl[i], j, k);
			if (!inf[i] || !inf[i][k++])
				return (0);
		}
		else if (!ft_strcmp(cmdl[i][j], "<<"))
		{
			remove_array_elements((void **)cmdl[i], j, j + 1, free);
			extract_name(inf + i, hd_dup, 0, k);
			if (!inf[i] || !inf[i][k++])
				return (0);
		}
		else
			j++;
	}
	return (1);
}

static void	extract_name(char ***curr_inf, char **curr_src, size_t j, size_t k)
{
	char	*extracted;

	if (!*curr_inf)
		*curr_inf = (char **)extract_array_elements((void **)curr_src, j, j);
	else
	{
		extracted = extract_array_element((void **)curr_src, j);
		insert_array_element((void ***)curr_inf, extracted, k);
	}
	return ;
}

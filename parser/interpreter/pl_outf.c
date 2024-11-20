/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_outf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:09:01 by libousse          #+#    #+#             */
/*   Updated: 2024/11/20 12:32:59 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static int	set_outf_arr(char ***cmdl, t_outf **outf, size_t i);
static int	set_outf_arr_elem(char **cmdl, t_outf *outf, size_t *j, size_t *k);

t_outf	**get_pl_outf(t_pl *pl)
{
	size_t	i;
	size_t	j;
	size_t	k;
	t_outf	**outf;

	outf = ft_calloc(pl->len + 1, sizeof(t_outf *));
	if (!outf)
		return (0);
	i = 0;
	while (pl->cmdl[i])
	{
		if (!set_outf_arr(pl->cmdl, outf, i))
			return (destroy_pl_outf(outf));
		j = 0;
		k = 0;
		while (pl_skip_parentheses(pl->cmdl[i], &j))
		{
			if (!set_outf_arr_elem(pl->cmdl[i], outf[i], &j, &k))
				return (destroy_pl_outf(outf));
		}
		++i;
	}
	return (outf);
}

void	*destroy_pl_outf(t_outf **outf)
{
	size_t	i;
	size_t	j;

	if (!outf)
		return (0);
	i = 0;
	while (outf[i])
	{
		j = 0;
		while (outf[i][j].filename)
		{
			free(outf[i][j].filename);
			++j;
		}
		free(outf[i]);
		++i;
	}
	free(outf);
	return (0);
}

static int	set_outf_arr(char ***cmdl, t_outf **outf, size_t i)
{
	size_t	j;
	size_t	len;

	j = 0;
	len = 0;
	while (pl_skip_parentheses(cmdl[i], &j))
	{
		len += !ft_strcmp(cmdl[i][j], ">") || !ft_strcmp(cmdl[i][j], ">>");
		++j;
	}
	outf[i] = ft_calloc(len + 1, sizeof(t_outf));
	return (outf[i] != 0);
}

static int	set_outf_arr_elem(char **cmdl, t_outf *outf, size_t *j, size_t *k)
{
	int	flags;

	if (!ft_strcmp(cmdl[*j], ">") || !ft_strcmp(cmdl[*j], ">>"))
	{
		if (!ft_strcmp(cmdl[*j], ">"))
			flags = O_CREAT | O_WRONLY | O_TRUNC;
		else
			flags = O_CREAT | O_WRONLY | O_APPEND;
		remove_array_elements((void **)cmdl, *j, *j, free);
		outf[*k].filename = extract_array_element((void **)cmdl, *j);
		outf[*k].flags = flags;
		if (!outf[*k].filename)
			return (0);
		++*k;
	}
	else
		++*j;
	return (1);
}

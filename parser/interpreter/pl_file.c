/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:09:01 by libousse          #+#    #+#             */
/*   Updated: 2024/11/26 13:30:49 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static int	set_file_arr(char ***cmdl, t_file **file, size_t i);
static int	set_file_arr_elem(char **cmdl, t_file *file, size_t *j, size_t *k);
static int	is_file_indicator(const char *s);

t_file	**get_pl_file(t_pl *pl)
{
	size_t	i;
	size_t	j;
	size_t	k;
	t_file	**file;

	file = ft_calloc(pl->len + 1, sizeof(t_file *));
	if (!file)
		return (0);
	i = 0;
	while (pl->cmdl[i])
	{
		if (!set_file_arr(pl->cmdl, file, i))
			return (destroy_pl_file(file));
		j = 0;
		k = 0;
		while (pl_skip_parentheses(pl->cmdl[i], &j))
		{
			if (!set_file_arr_elem(pl->cmdl[i], file[i], &j, &k))
				return (destroy_pl_file(file));
		}
		++i;
	}
	return (file);
}

void	*destroy_pl_file(t_file **file)
{
	size_t	i;
	size_t	j;

	if (!file)
		return (0);
	i = 0;
	while (file[i])
	{
		j = 0;
		while (file[i][j].filename)
		{
			free(file[i][j].filename);
			++j;
		}
		free(file[i]);
		++i;
	}
	free(file);
	return (0);
}

static int	set_file_arr(char ***cmdl, t_file **file, size_t i)
{
	size_t	j;
	size_t	len;

	j = 0;
	len = 0;
	while (pl_skip_parentheses(cmdl[i], &j))
		len += is_file_indicator(cmdl[i][j++]) >= 0;
	file[i] = ft_calloc(len + 1, sizeof(t_file));
	return (file[i] != 0);
}

static int	set_file_arr_elem(char **cmdl, t_file *file, size_t *j, size_t *k)
{
	int	flags;
	int	io;

	io = is_file_indicator(cmdl[*j]);
	if (io >= 0)
	{
		flags = O_RDONLY;
		if (!ft_strcmp(cmdl[*j], ">"))
			flags = O_CREAT | O_WRONLY | O_TRUNC;
		else if (!ft_strcmp(cmdl[*j], ">>"))
			flags = O_CREAT | O_WRONLY | O_APPEND;
		remove_array_elements((void **)cmdl, *j, *j, free);
		file[*k].filename = extract_array_element((void **)cmdl, *j);
		file[*k].flags = flags;
		file[*k].io = io;
		if (!file[*k].filename)
			return (0);
		++*k;
	}
	else
		++*j;
	return (1);
}

static int	is_file_indicator(const char *s)
{
	if (!ft_strcmp(s, "<") || !ft_strcmp(s, "<<"))
		return (0);
	else if (!ft_strcmp(s, ">") || !ft_strcmp(s, ">>"))
		return (1);
	return (-1);
}

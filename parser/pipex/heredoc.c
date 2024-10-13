/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:16:20 by libousse          #+#    #+#             */
/*   Updated: 2024/09/17 17:29:42 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	populate_array(int **heredocs, int i, char *delimiter, int *code);
static char	*compose_filename(int index, int index_heredoc);

/*
	Each subprocess can have several heredocs. The code is simplified in Pipex, 
	with only the first subprocess having a potential heredoc.
*/

int	*get_favor_hd_array(t_pl *pl)
{
	int	*arr;
	int	i;

	arr = malloc(pl->len * sizeof(int));
	if (!arr)
		return (0);
	i = 0;
	while (i < pl->len)
	{
		arr[i] = 1;
		++i;
	}
	return (arr);
}

int	**get_heredocs(int pl_len, char *delimiter, int *exit_code)
{
	int	**heredocs;
	int	i;

	heredocs = ft_calloc(pl_len + 1, sizeof(int *));
	if (!heredocs)
	{
		*exit_code = ENOMEM;
		return (0);
	}
	i = 0;
	while (i < pl_len)
	{
		heredocs[i] = malloc((1 + (!i && delimiter != 0)) * sizeof(int));
		if (!heredocs[i])
		{
			*exit_code = ENOMEM;
			free_heredocs(heredocs);
			return (0);
		}
		if (!populate_array(heredocs, i, delimiter, exit_code))
			return (0);
		++i;
	}
	return (heredocs);
}

static int	populate_array(int **heredocs, int i, char *delimiter, int *code)
{
	char	*tmp_filename;

	heredocs[i][0] = -1;
	if (!i && delimiter)
	{
		tmp_filename = compose_filename(i, 0);
		if (!tmp_filename)
		{
			*code = ENOMEM;
			return (0);
		}
		heredocs[i][0] = create_heredoc(tmp_filename, delimiter, code);
		heredocs[i][1] = -1;
		free(tmp_filename);
		if (heredocs[i][0] < 0)
		{
			free_heredocs(heredocs);
			return (0);
		}
	}
	return (1);
}

static char	*compose_filename(int index, int index_heredoc)
{
	char	*name1;
	char	*name2;
	char	*nbr;

	nbr = ft_itoa(index);
	name1 = ft_strjoin("~heredoc", nbr);
	free(nbr);
	name2 = ft_strjoin(name1, "_");
	free(name1);
	nbr = ft_itoa(index_heredoc);
	name1 = ft_strjoin(name2, nbr);
	free(nbr);
	free(name2);
	name2 = ft_strjoin(name1, ".tmp");
	free(name1);
	return (name2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirected_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:21:47 by libousse          #+#    #+#             */
/*   Updated: 2024/09/17 17:29:51 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Each subprocess can have several redirected input and output files. The 
	code is simplified in Pipex, with only the first subprocess having an input 
	file (if not a heredoc), and only the last subprocess having an output file.
*/

char	***get_infiles(int pl_len, char *infile)
{
	char	***infiles;
	int		i;

	infiles = ft_calloc(pl_len + 1, sizeof(char **));
	if (!infiles)
		return (0);
	i = 0;
	while (i < pl_len)
	{
		infiles[i] = ft_calloc(1 + (!i && infile != 0), sizeof(char *));
		if (!infiles[i])
		{
			free_infiles(infiles);
			return (0);
		}
		infiles[i][0] = 0;
		if (!i && infile)
			infiles[i][0] = ft_strdup(infile);
		++i;
	}
	return (infiles);
}

t_outf	**get_outfiles(int pl_len, char *outfile, int flags)
{
	t_outf	**outfiles;
	int		i;

	outfiles = ft_calloc(pl_len + 1, sizeof(t_outf *));
	if (!outfiles)
		return (0);
	i = 0;
	while (i < pl_len)
	{
		outfiles[i] = ft_calloc(1 + ((i == pl_len - 1) && outfile != 0),
				sizeof(t_outf));
		if (!outfiles[i])
		{
			free_outfiles(outfiles);
			return (0);
		}
		outfiles[i][0].filename = 0;
		if (i == pl_len - 1 && outfile)
		{
			outfiles[i][0].filename = ft_strdup(outfile);
			outfiles[i][0].flags = flags;
		}
		++i;
	}
	return (outfiles);
}

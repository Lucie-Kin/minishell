/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bn_joinline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:11:14 by lchauffo          #+#    #+#             */
/*   Updated: 2024/09/28 18:34:26 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbn.h"

char	**bn_joinline(char **file, char *line)
{
	char	**joined;
	int		len_file;
	int		len_lastln;
	int		nline;

	if (!file || !line)
		return (0);
	nline = bn_linelen(file);
	len_file = nline;
	joined = malloc(sizeof(char *) * (len_file + 2));
	if (!joined)
		return (0);
	nline = 0;
	while (file[nline])
	{
		joined[nline] = ft_strdup(file[nline]);
		nline++;
	}
	len_lastln = ft_strlen(joined[nline - 1]);
	joined[nline - 1][len_lastln] = '\n';
	joined[nline] = ft_strdup(line);
	len_lastln = ft_strlen(line);
	joined[nline][len_lastln] = '\0';
	joined[nline + 1] = NULL;
	return (joined);
}

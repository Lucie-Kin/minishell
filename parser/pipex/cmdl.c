/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:48:32 by libousse          #+#    #+#             */
/*   Updated: 2024/10/12 18:13:18 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*remove_twin_quotes(const char *s);

char	***parse_cmdl(char **args, int arg_len)
{
	int		i;
	char	*arg;
	char	***cmdl;

	cmdl = ft_calloc(arg_len + 1, sizeof(char **));
	if (!cmdl)
		return (0);
	i = 0;
	while (i < arg_len)
	{
		arg = remove_twin_quotes(args[i]);
		cmdl[i] = ft_split(arg, 31);
		free(arg);
		if (!cmdl[i])
		{
			free_cmdl(cmdl);
			return (0);
		}
		++i;
	}
	return (cmdl);
}

void	free_cmdl(char ***cmdl)
{
	size_t	i;
	size_t	j;

	if (!cmdl)
		return ;
	i = 0;
	while (cmdl[i])
	{
		j = 0;
		while (cmdl[i][j])
		{
			free(cmdl[i][j]);
			++j;
		}
		free(cmdl[i]);
		++i;
	}
	free(cmdl);
	return ;
}

static char	*remove_twin_quotes(const char *s)
{
	size_t	i;
	char	*parsed;
	char	*quote;

	parsed = ft_strdup(s);
	if (!parsed)
		return (0);
	quote = 0;
	i = -1;
	while (parsed[++i])
	{
		if (!quote && ft_isspace(parsed[i]))
			parsed[i] = 31;
		else if (!quote && (parsed[i] == '\'' || parsed[i] == '"'))
			quote = parsed + i;
		else if (quote && *quote == parsed[i])
		{
			ft_memmove(quote, quote + 1, ft_strlen(quote + 1) + 1);
			--i;
			ft_memmove(parsed + i, parsed + i + 1, ft_strlen(parsed + i + 1) + 1);
			--i;
			quote = 0;
		}
	}
	return (parsed);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:48:32 by libousse          #+#    #+#             */
/*   Updated: 2024/09/17 17:40:00 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define FS 28
#define GS 29
#define RS 30
#define US 31

/*
	- ASCII 31 (Unit Separator - US):
		Separates the smallest units, like individual arguments or fields.
	- ASCII 30 (Record Separator - RS):
		Separates entire records, like commands in a pipeline.
	- ASCII 29 (Group Separator - GS):
		Separates groups of records or commands.
	- ASCII 28 (File Separator - FS):
		Separates large chunks of data, like files or major sections.
*/

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
		cmdl[i] = ft_split(arg, US);
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
			parsed[i] = US;
		else if (!quote && (parsed[i] == '\'' || parsed[i] == '"'))
			quote = parsed + i;
		else if (quote && *quote == parsed[i])
		{
			ft_memmove(quote, quote + 1, ft_strlen(quote));
			--i;
			ft_memmove(parsed + i, parsed + i + 1, ft_strlen(parsed + i));
			--i;
			quote = 0;
		}
	}
	return (parsed);
}

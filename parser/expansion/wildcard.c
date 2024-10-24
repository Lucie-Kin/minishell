/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 18:26:37 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/24 12:28:34 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static char	**get_cwd_content(const char *s);

static void	filter_to_match_wildcards(char *arg, char ***expand);
static int	start_with_wildcard(char *arg, char **expand, int *i);
static int	match_pattern_wildcard(char *arg, char **expand, int *i, int *j);
static int	end_with_wildcard(char *arg_i, char **expand, int j);

char	**get_wildcards(const char *s)
{
	char	**cwd_content;

	cwd_content = get_cwd_content(s);
	if (!cwd_content)
		return (0);
	if (bn_onlychar((char *)s, '*'))
		return (cwd_content);
	/*
		Check the pattern's path to tell whether we should return anything at all.
		Current directory only.
	   ---
		THIS FUNCTION
		*.*  -> . .. .git .gitattributes .gitignore .vscode main.c main.o minishell.h readline.supp README.md 
		*..* -> ..

		BASH
		*.*  -> main.c main.o minishell.h readline.supp README.md
		*..* -> [None]
	*/
	filter_to_match_wildcards((char *)s, &cwd_content);
	return (cwd_content);
}

static char	**get_cwd_content(const char *s)
{
	size_t			i;
	char			**arr;
	DIR				*dir;
	struct dirent	*ent;

	arr = 0;
	dir = opendir(".");
	if (!dir)
		return (0);
	i = 0;
	ent = readdir(dir);
	while (ent)
	{
		if (!bn_onlychar((char *)s, '*') || ent->d_name[0] != '.')
		{
			insert_array_element((void ***)&arr, (void *)ft_strdup(ent->d_name),
				i++);
			if (!arr || !arr[i - 1])
				break ;
		}
		ent = readdir(dir);
	}
	closedir(dir);
	sort_strings(arr);
	return (arr);
}

static void	filter_to_match_wildcards(char *arg, char ***expand)
{
	int	i;
	int	j;
	int	k;
	int	valid;

	k = 0;
	i = 0;
	while (expand && *expand && (*expand)[k])
	{
		valid = start_with_wildcard(arg, &(*expand)[k], &i);
		j = i;
		while (valid && arg[i])
		{
			if (arg[i] == '*')
				i += bn_countiter(arg + i, '*');
			else if (arg[i] != '*')
				valid = match_pattern_wildcard(arg, &(*expand)[k], &i, &j);
		}
		if (arg[i] == '\0')
			valid = end_with_wildcard(&arg[--i], &(*expand)[k], j);
		if (!valid)
		{
			remove_array_elements((void **)*expand, k, k, free);
			--k;
		}
		++k;
	}
	return ;
}

static int	start_with_wildcard(char *arg, char **expand, int *i)
{
	int	size;
	int	dif;

	*i = 0;
	if (!expand || !*expand || !arg)
		return (0);
	if (arg[*i] != '*')
	{
		size = bn_strnlen(arg + *i, '*');
		dif = ft_strncmp((*expand), arg + *i, size);
		if (dif)
			return (0);
		*i += size;
	}
	return (1);
}

static int	match_pattern_wildcard(char *arg, char **expand, int *i, int *j)
{
	int	word;

	if (!expand || !*expand || !arg)
		return (0);
	word = bn_strnlen(arg + *i, '*');
	while ((*expand)[*j])
	{
		if (ft_strncmp((*expand) + *j, arg + *i, word) == 0)
		{
			*i += word;
			*j += word;
			return (1);
		}
		++*j;
	}
	return (0);
}

static int	end_with_wildcard(char *arg_i, char **expand, int j)
{
	if ((*arg_i) != '*')
	{
		if ((*expand) && (*expand)[j] != '\0')
			return (0);
	}
	return (1);
}

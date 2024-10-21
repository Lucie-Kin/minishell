/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 18:26:37 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/21 14:38:50 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"
#include "test.h"

//bash: gnl/get_next_line.c: Permission denied --> Feature not included

int	end_with_wildcard(char *arg_i, char **expand, int j)
{
	if ((*arg_i) != '*')
	{
		if ((*expand) && (*expand)[j] != '\0')
			return (FALSE);
	}
	return (TRUE);
}

int	match_pattern_wildcard(char *arg, char **expand, int *i, int *j)
{
	int	word;

	if (!expand || !*expand || !arg)
		return (FALSE);
	word = bn_strnlen(arg + *i, '*');
	while ((*expand)[*j])
	{
		if (ft_strncmp((*expand) + *j, arg + *i, word) == 0)
		{
			*i += word;
			*j += word;
			return (TRUE);
		}
		(*j)++;
	}
	return (FALSE);
}

int	start_with_wildcard(char *arg, char **expand, int *i)
{
	int		size;
	int		dif;

	*i = 0;
	if (!expand || !*expand || !arg)
		return (FALSE);
	if (arg[*i] != '*')
	{
		size = bn_strnlen(arg + *i, '*');
		dif = ft_strncmp((*expand), arg + *i, size);
		if (dif != 0)
			return (FALSE);
		*i += size;
	}
	return (TRUE);
}

void	filter_to_match_wildcards(char *arg, char ***expand)
{
	int		i;
	int		j;
	int		k;
	int		valid;

	k = 0;
	i = 0;
	while (expand && *expand && (*expand)[k])
	{
		valid = start_with_wildcard(arg, &(*expand)[k], &i);
		j = i;
		while (valid == TRUE && arg[i])
		{
			if (arg[i] == '*')
				i += bn_countiter(arg + i, '*');
			else if (arg[i] != '*')
				valid = match_pattern_wildcard(arg, &(*expand)[k], &i, &j);
		}
		if (arg[i] == '\0')
			valid = end_with_wildcard(&arg[--i], &(*expand)[k], j);
		if (valid == FALSE)
			remove_tab_elements(expand, k--);
		k++;
	}
}

char	**bigerrno_wildcard(const char *arg)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**expand;
	int				count;
	int				i;

	i = 0;
	count = init_expand(&expand);
	if (!expand || count == -1)
		return (perror("Initialization of expand impossible"), NULL);
	dir = opendir(".");
	if (!dir)
		return (perror("Actual directory not found"), NULL);
	entry = readdir(dir);
	while (entry && i < count)
	{
		expand[i++] = ft_strdup(entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
	if (bn_onlychar((char *)arg, '*'))
		return (clean_expand(expand));
	else
		filter_to_match_wildcards((char *)arg, &expand);
	return (expand);
}

// int	main(int argc, char **argv)
// {
// 	char	**print;
// 	char	*arg;

// 	if (argc == 2)
// 	{
// 		arg = ft_strdup(argv[1] + 1);
// 		if (argv[1][0] == '*')
// 		{
// 			print = bigerrno_wildcard(arg);
// 			print_wildcard(print);
// 		}
// 		else
// 			return (free(arg), 0);
// 	}
// 	else
// 		return (0);
// 	bn_freetab(print);
// 	free(arg);
// 	return (0);
// }

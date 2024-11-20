/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_wildcard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:10:37 by libousse          #+#    #+#             */
/*   Updated: 2024/11/02 17:18:50 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static void	get_path_and_pattern(const char *s, char **path, char **pattern);
static int	is_pattern_for_dirs(char **pattern);
static int	wildcard_cmp(const char *s1, const char *s2);
static void	prepend_path(const char *path, char **content);

char	**expand_asterisk_wildcard(const char *s)
{
	char	*path;
	char	*pattern;
	char	**content;
	int		only_dirs;

	path = 0;
	pattern = 0;
	get_path_and_pattern(s, &path, &pattern);
	only_dirs = is_pattern_for_dirs(&pattern);
	if (!path || !pattern)
	{
		free(path);
		free(pattern);
		return (0);
	}
	content = get_filtered_dir_content(path, pattern, only_dirs);
	sort_strings_alpha(content, wildcard_cmp);
	prepend_path(path, content);
	free(path);
	free(pattern);
	return (content);
}

static void	get_path_and_pattern(const char *s, char **path, char **pattern)
{
	size_t	path_len;
	char	*p_slash;
	char	*p_asterisk;

	p_asterisk = ft_strchr(s, '*');
	if (!p_asterisk)
		return ;
	*path = ft_substr(s, 0, p_asterisk - s);
	if (!*path)
		return ;
	p_slash = ft_strrchr(*path, '/');
	if (p_slash)
	{
		p_slash[1] = 0;
		path_len = ft_strlen(*path);
		*pattern = ft_substr(s, path_len, ft_strlen(s + path_len));
	}
	else
	{
		free(*path);
		*path = ft_strdup(".");
		*pattern = ft_strdup(s);
	}
	return ;
}

/*
	The `bn_onlychar` bit is in order to abort if the pattern is about subdirs, 
	as this feature is not implemented. The pattern matching only happens in 
	the current directory of said path.

	Also note that there can be more than one asterisk in a row, interpret them 
	as one. Having more than one asterisk is only relevant when searching 
	subdirectories.
*/
static int	is_pattern_for_dirs(char **pattern)
{
	char	*p_slash;
	char	*tmp;

	if (!*pattern)
		return (0);
	p_slash = ft_strchr(*pattern, '/');
	if (p_slash)
	{
		if (!bn_onlychar(p_slash, '/'))
		{
			free(*pattern);
			*pattern = 0;
		}
		else
		{
			tmp = ft_substr(*pattern, 0, p_slash - *pattern);
			free(*pattern);
			*pattern = tmp;
			return (1);
		}
	}
	return (0);
}

static int	wildcard_cmp(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	int		diff;

	i = 0;
	j = 0;
	while (s1[i] && s2[j])
	{
		if (ft_isalnum(s1[i]) && ft_isalnum(s2[j]))
		{
			diff = (unsigned char)ft_toupper(s1[i++])
				- (unsigned char)ft_toupper(s2[j++]);
			if (diff)
				return (diff);
		}
		else
		{
			if (!ft_isalnum(s1[i]))
				++i;
			if (!ft_isalnum(s2[j]))
				++j;
		}
	}
	return ((unsigned char)ft_toupper(s1[i])
		- (unsigned char)ft_toupper(s2[j]));
}

static void	prepend_path(const char *path, char **content)
{
	size_t	i;
	char	*tmp;

	if (!ft_strcmp(path, ".") || !content)
		return ;
	i = 0;
	while (content[i])
	{
		tmp = ft_strjoin(path, content[i]);
		if (tmp)
		{
			free(content[i]);
			content[i] = tmp;
		}
		++i;
	}
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_wildcard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:10:37 by libousse          #+#    #+#             */
/*   Updated: 2024/10/26 20:59:00 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static char	**get_filtered_cwd_content(const char *s, int only_dirs);
static int	is_correct_file(const char *s, struct dirent *ent, int only_dirs);
static int	add_name(char ***arr, size_t i, struct dirent *ent, int only_dirs);

char	**expand_asterisk_wildcard(const char *s)
{
	char	*p_slash;
	char	*pattern;
	char	**content;

	p_slash = ft_strchr(s, '/');
	if (p_slash && (s[0] == '/' || !bn_onlychar(p_slash, '/')))
		return (0);
	pattern = (char *)s;
	if (p_slash)
	{
		pattern = ft_substr(s, 0, p_slash - s);
		if (!pattern)
			return (0);
	}
	content = get_filtered_cwd_content(pattern, p_slash != 0);
	sort_strings_alpha(content, ft_strcasecmp);
	if (p_slash)
		free(pattern);
	return (content);
}

static char	**get_filtered_cwd_content(const char *s, int only_dirs)
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
		if (is_correct_file(s, ent, only_dirs))
		{
			if (!add_name(&arr, i, ent, only_dirs))
				break ;
			++i;
		}
		ent = readdir(dir);
	}
	closedir(dir);
	return (arr);
}

static int	is_correct_file(const char *s, struct dirent *ent, int only_dirs)
{
	char	*file;
	char	*p_start;
	char	*p_end;

	if (!s || !ent)
		return (0);
	else if (only_dirs && ent->d_type != DT_DIR)
		return (0);
	else if (s[0] == '.' && ent->d_name[0] != '.')
		return (0);
	else if (s[0] != '.' && ent->d_name[0] == '.')
		return (0);
	file = ent->d_name;
	p_start = (char *)s;
	p_end = ft_strchr(p_start, '*');
	while (p_end)
	{
		if (!file || ft_strncmp(file, p_start, p_end - p_start) != 0)
			return (0);
		p_start = p_end + 1;
		p_end = ft_strchr(p_start, '*');
		if (p_start != p_end)
			file = ft_strchr(file + 1, p_start[0]);
	}
	return (!(p_start && (!file || ft_strcmp(file, p_start) != 0)));
}

static int	add_name(char ***arr, size_t i, struct dirent *ent, int only_dirs)
{
	char	*name;

	if (only_dirs)
		name = ft_strjoin(ent->d_name, "/");
	else
		name = ft_strdup(ent->d_name);
	if (!name)
		return (0);
	insert_array_element((void ***)arr, (void *)name, i);
	if (!*arr || !(*arr)[i])
	{
		free(name);
		return (0);
	}
	return (1);
}

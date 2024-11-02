/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filtered_dir_content.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:02:27 by libousse          #+#    #+#             */
/*   Updated: 2024/11/02 16:04:47 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static int	is_correct_file(const char *path, const char *pattern,
				struct dirent *ent, int only_dirs);
static int	is_dirent_a_directory(struct dirent *ent, const char *path);
static int	add_name(char ***arr, size_t i, struct dirent *ent, int only_dirs);

char	**get_filtered_dir_content(const char *path, const char *pattern,
	int only_dirs)
{
	size_t			i;
	char			**arr;
	DIR				*dir;
	struct dirent	*ent;

	arr = 0;
	dir = opendir(path);
	if (!dir)
		return (0);
	i = 0;
	ent = readdir(dir);
	while (ent)
	{
		if (is_correct_file(path, pattern, ent, only_dirs))
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

static int	is_correct_file(const char *path, const char *pattern,
	struct dirent *ent, int only_dirs)
{
	char	*file;
	char	*p_start;
	char	*p_end;

	if (!pattern || !ent)
		return (0);
	else if (only_dirs && !is_dirent_a_directory(ent, path))
		return (0);
	else if (pattern[0] == '.' && ent->d_name[0] != '.')
		return (0);
	else if (pattern[0] != '.' && ent->d_name[0] == '.')
		return (0);
	file = ent->d_name;
	p_start = (char *)pattern;
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

static int	is_dirent_a_directory(struct dirent *ent, const char *path)
{
	int			is_dir;
	char		*fullpath;
	struct stat	statbuf;

	if (!ent)
		return (0);
	else if (ent->d_type == DT_DIR)
		return (1);
	fullpath = ft_strjoin(path, ent->d_name);
	if (!fullpath)
		return (0);
	is_dir = stat(fullpath, &statbuf) == 0 && S_ISDIR(statbuf.st_mode);
	free(fullpath);
	return (is_dir);
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

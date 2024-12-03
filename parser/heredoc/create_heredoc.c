/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:55:49 by libousse          #+#    #+#             */
/*   Updated: 2024/12/03 23:29:22 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	fetch_heredoc(t_sh *sh, size_t *index, const char *delimiter);
static int	compare_delimiter_and_line(const char *del, const char *line);
static int	write_line_to_file(t_sh *sh, int fd, const char *s);
static char	*get_expanded_heredoc_line(t_sh *sh, const char *s, char *tmp1);

int	create_heredoc(t_sh *sh, size_t hd_index, size_t *index,
	const char *delimiter)
{
	int		fd;
	size_t	curr_line;
	size_t	last_line;

	insert_array_element((void ***)&sh->rl.hd,
		(void *)compose_heredoc_name(hd_index), hd_index);
	if (!sh->rl.hd[hd_index])
		return (0);
	curr_line = *index;
	if (!fetch_heredoc(sh, index, delimiter))
		return (0);
	last_line = *index;
	fd = open(sh->rl.hd[hd_index], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd < 0)
		return (0);
	while (++curr_line < last_line
		&& ft_strcmp(sh->rl.arr[curr_line]->value, delimiter))
	{
		if (!write_line_to_file(sh, fd, sh->rl.arr[curr_line]->value))
			return (0);
	}
	close(fd);
	return (1);
}

static int	fetch_heredoc(t_sh *sh, size_t *index, const char *delimiter)
{
	char	*line;

	if (!sh->rl.buf || !sh->rl.buf[0])
		add_input_to_buffer(sh, "> ");
	while (sh->rl.buf && sh->rl.buf[0])
	{
		++*index;
		extract_first_buffer_line(sh, index, 1);
		if (!sh->rl.arr[*index])
		{
			--*index;
			return (0);
		}
		get_prefix_for_backslashes(sh, *index, 0);
		line = sh->rl.arr[*index]->value;
		if (compare_delimiter_and_line(delimiter, line))
			return (1);
		if (!sh->rl.buf || !sh->rl.buf[0])
			add_input_to_buffer(sh, "> ");
	}
	if (g_signum == EOF)
		heredoc_ctrl_d(index, delimiter);
	return (1);
}

static int	compare_delimiter_and_line(const char *del, const char *line)
{
	size_t	len_del;
	size_t	len_line;
	size_t	len_max;

	if (!del || !line)
		return (1);
	len_del = ft_strlen(del);
	if (!len_del)
		return (1);
	len_line = ft_strlen(line);
	if (!len_line)
		return (0);
	if (line[len_line - 1] == '\n')
		--len_line;
	len_max = len_del;
	if (len_line > len_del)
		len_max = len_line;
	return (!ft_strncmp(del, line, len_max));
}

static int	write_line_to_file(t_sh *sh, int fd, const char *s)
{
	size_t	i;
	int		success;
	char	*tmp1;
	char	*tmp2;

	success = 1;
	tmp1 = ft_strdup(s);
	i = 0;
	while (tmp1 && tmp1[i])
	{
		if (tmp1[i] == '\\' && tmp1[i + 1] == '\\')
		{
			tmp2 = remove_str(tmp1, i, 1);
			free(tmp1);
			tmp1 = tmp2;
		}
		++i;
	}
	if (!tmp1)
		tmp1 = (char *)s;
	tmp1 = get_expanded_heredoc_line(sh, s, tmp1);
	if (write(fd, tmp1, ft_strlen(tmp1)) < 0)
		success = 0;
	free(tmp1);
	return (success);
}

static char	*get_expanded_heredoc_line(t_sh *sh, const char *s, char *tmp1)
{
	char	*dup;

	if (!tmp1)
		return (0);
	dup = expand_environment_variables(sh, tmp1);
	if (s != tmp1)
		free(tmp1);
	return (dup);
}

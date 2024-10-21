/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:55:49 by libousse          #+#    #+#             */
/*   Updated: 2024/10/19 20:42:13 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	create_heredoc(t_sh *sh, size_t hd_index, size_t *index,
				const char *delimiter);
static char	*compose_heredoc_name(size_t index);
static int	fetch_heredoc(t_sh *sh, size_t *index, const char *delimiter);
static int	write_line_to_file(int fd, const char *s);

int	handle_heredoc_content(t_sh *sh, size_t *index)
{
	size_t	i;
	size_t	i_hd;
	size_t	cmdl_index;

	cmdl_index = *index;
	if (!sh->rl.arr[cmdl_index]->delimiters)
		return (1);
	i = 0;
	i_hd = get_array_length((void **)sh->rl.hd);
	while (sh->rl.arr[cmdl_index]->delimiters[i])
	{
		if (!create_heredoc(sh, i_hd, index,
				sh->rl.arr[cmdl_index]->delimiters[i]))
		{
			if (sh->rl.hd[i_hd])
			{
				unlink(sh->rl.hd[i_hd]);
				remove_array_elements((void **)sh->rl.hd, i_hd, i_hd, free);
			}
			return (0);
		}
		++i;
		++i_hd;
	}
	return (1);
}

static char	*compose_heredoc_name(size_t index)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_itoa(index);
	tmp2 = ft_strjoin(".heredoc", tmp1);
	free(tmp1);
	tmp1 = ft_strjoin(tmp2, ".tmp");
	free(tmp2);
	return (tmp1);
}

static int	create_heredoc(t_sh *sh, size_t hd_index, size_t *index,
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
	while (++curr_line <= last_line
		&& ft_strcmp(sh->rl.arr[curr_line]->value, delimiter))
	{
		if (!write_line_to_file(fd, sh->rl.arr[curr_line]->value))
			return (0);
	}
	close(fd);
	return (1);
}

static int	fetch_heredoc(t_sh *sh, size_t *index, const char *delimiter)
{
	char	*line;

	// Signal handling probably in `add_input_to_buffer` and the loop condition
	while (1)
	{
		if (!sh->rl.buf[0])
			add_input_to_buffer(sh, "> ");
		if (!sh->rl.buf[0])
			return (0);
		++*index;
		extract_first_buffer_line(sh, index, 1);
		if (!sh->rl.arr[*index])
		{
			--*index;
			return (0);
		}
		get_prefix_for_backslashes(sh, *index, 0);
		line = sh->rl.arr[*index]->value;
		if (!ft_strcmp(line, delimiter))
			return (1);
	}
	return (1);
}

static int	write_line_to_file(int fd, const char *s)
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
	if (!(write(fd, tmp1, ft_strlen(tmp1)) >= 0 && write(fd, "\n", 1) == 1))
		success = 0;
	if (tmp1 != s)
		free(tmp1);
	return (success);
}

/*
static char	*heredoc_line_prompt(char *delimiter)
{
	char	*line;

	write(1, "> ", 2);
	line = get_next_line(0);
	if (!line)
	{
		ft_putstr_fd("\n", 1);
		ft_putstr_fd(SHELL_NAME, 1);
		ft_putstr_fd(": warning: here-document delimited by end-of-file ", 1);
		ft_putstr_fd("(wanted `", 1);
		ft_putstr_fd(delimiter, 1);
		ft_putstr_fd("')\n", 1);
	}
	return (line);
}
*/

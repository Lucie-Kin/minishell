/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:41:41 by libousse          #+#    #+#             */
/*   Updated: 2024/09/17 18:00:35 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	max_size_t(size_t a, size_t b);
static int		write_to_heredoc(int fd, char *delimiter, int *code);
static char		*heredoc_line_prompt(char *delimiter);

int	create_heredoc(char *tmp_filename, char *delimiter, int *code)
{
	int	fd;
	int	written_successfully;

	fd = open(tmp_filename, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (fd < 0)
	{
		*code = errno;
		return (-1);
	}
	written_successfully = write_to_heredoc(fd, delimiter, code);
	close(fd);
	if (written_successfully)
	{
		fd = open(tmp_filename, O_RDONLY);
		if (fd < 0)
			*code = errno;
	}
	unlink(tmp_filename);
	if (!written_successfully)
		return (-1);
	return (fd);
}

static size_t	max_size_t(size_t a, size_t b)
{
	if (a > b)
		return (a);
	return (b);
}

static int	write_to_heredoc(int fd, char *delimiter, int *code)
{
	char	*line;
	size_t	del_len;
	size_t	line_len;

	del_len = ft_strlen(delimiter);
	line = heredoc_line_prompt(delimiter);
	while (line)
	{
		line_len = ft_strlen(line);
		if (!ft_strncmp(delimiter, line, max_size_t(del_len, line_len - 1)))
		{
			free(line);
			break ;
		}
		if (write(fd, line, line_len) < 0)
		{
			*code = errno;
			free(line);
			return (0);
		}
		free(line);
		line = heredoc_line_prompt(delimiter);
	}
	return (1);
}

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
		ft_putstr_fd("`)\n", 1);
	}
	return (line);
}

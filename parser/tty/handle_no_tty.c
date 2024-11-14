/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_no_tty.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:32:16 by libousse          #+#    #+#             */
/*   Updated: 2024/11/14 16:37:54 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_each_line(int fd);

void	handle_no_tty(void)
{
	int	is_stdout_tty;
	int	res;

	errno = 0;
	is_stdout_tty = isatty(STDOUT_FILENO);
	if (errno == ENOTTY)
		exit(ENOTTY);
	set_signal_handling(SIGPIPE, SIG_IGN);
	res = !is_stdout_tty && write(1, "", 1) < 0 && errno == EPIPE;
	set_signal_handling(SIGPIPE, SIG_DFL);
	if (res)
		exit(EPIPE);
	if (!isatty(STDIN_FILENO))
		execute_each_line(STDIN_FILENO);
	return ;
}

static void	execute_each_line(int fd)
{
	size_t	i;
	char	*line;
	char	*str_itoa;
	char	*str_line_num;

	i = 1;
	line = get_next_line(fd);
	while (line)
	{
		str_itoa = ft_itoa(i);
		str_line_num = ft_strjoin("line ", str_itoa);
		line[ft_strlen(line) - 1] = 0;
		output_error(1, compose_err_msg(SHELL, str_line_num, line, "nope"));
		free(str_itoa);
		free(str_line_num);
		free(line);
		line = get_next_line(fd);
		++i;
	}
	exit(EPERM);
	return ;
}

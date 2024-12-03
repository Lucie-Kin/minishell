/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:49:32 by lchauffo          #+#    #+#             */
/*   Updated: 2024/12/03 17:20:02 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define DOT "\e[35m•\e[0m"

static void	get_terminal_size(int *rows_cols);
static void	execute_in_child(int pipefd[2]);
static void	execute_in_parent(int pipefd[2], int *rows_cols);
static void	animate_shoot(int cols);

int	bigerrno_shoot(enum e_color *color, char **arg)
{
	int		rows_cols[2];

	if (get_array_length((void **)arg) > 1)
		perror("Don't shoot anything");
	write(1, PROMPT_COLOR_OPEN, ft_strlen(PROMPT_COLOR_OPEN));
	write(1, "  minishell$ ", 14);
	write(1, PROMPT_COLOR_CLOSE, ft_strlen(PROMPT_COLOR_CLOSE));
	get_terminal_size(rows_cols);
	animate_shoot(rows_cols[1]);
	*color = E_PINK;
	return (TRUE);
}

static void	get_terminal_size(int *rows_cols)
{
	int				cpid;
	int				pipefd[2];
	struct termios	oldt;
	struct termios	newt;

	tcgetattr(STDIN_FILENO, &oldt);
	ft_memcpy(&newt, &oldt, sizeof(struct termios));
	newt.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	if (pipe(pipefd) == -1)
		return (perror("Impossible pipe creation\n"));
	cpid = fork();
	if (cpid == -1)
		return (perror("Impossible child creation\n"));
	if (cpid == 0)
		execute_in_child(pipefd);
	else
	{
		execute_in_parent(pipefd, rows_cols);
		wait(NULL);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

static void	execute_in_child(int pipefd[2])
{
	char	buffer[124];
	int		n_bytes;

	close(pipefd[0]);
	write(STDOUT_FILENO, "\e[18t", 6);
	n_bytes = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
	if (n_bytes > 0)
	{
		buffer[n_bytes] = '\0';
		write(pipefd[1], buffer, ft_strlen(buffer));
	}
	close(pipefd[1]);
	exit(0);
}

static void	execute_in_parent(int pipefd[2], int *rows_cols)
{
	char	**split;
	char	buffer[124];
	int		n_bytes;

	close(pipefd[1]);
	n_bytes = read(pipefd[0], buffer, sizeof(buffer) - 1);
	buffer[n_bytes] = '\0';
	split = ft_split(buffer + 4, ';');
	if (split && split[0] && split[1])
	{
		rows_cols[0] = atoi(split[0]);
		rows_cols[1] = atoi(split[1]);
	}
	else
		printf("Erreur lors de la récupération des dimensions du terminal.\n");
	free_entire_array((void **)split, free);
	close(pipefd[0]);
}

static void	animate_shoot(int cols)
{
	int		pixel_pos;
	int		i;
	float	v;

	pixel_pos = -1;
	v = 0.1;
	while (++pixel_pos < cols && !g_signum)
	{
		write(STDOUT_FILENO, "\r", 1);
		i = -1;
		while (++i < pixel_pos)
			write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, DOT, ft_strlen(DOT));
		i = 0;
		while (i < 80000000 / v)
			++i;
		v += 0.2;
		if (v > 10.0)
			v = 10.0;
	}
	write(STDOUT_FILENO, "\r", 1);
	i = -1;
	while (++i < cols)
		write(STDOUT_FILENO, " ", 1);
	write(STDOUT_FILENO, "\r", 1);
}

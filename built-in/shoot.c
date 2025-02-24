/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:49:32 by lchauffo          #+#    #+#             */
/*   Updated: 2025/02/24 13:33:06 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigerrno.h"

static void	get_terminal_size(int *rows_cols);
static void	execute_in_child(int pipefd[2]);
static void	execute_in_parent(int pipefd[2], int *rows_cols);
static void	animate_shoot(int cols);

int	bigerrno_shoot(t_sh *sh, enum e_color *color, char **arg)
{
	int	rows_cols[2];

	if (get_array_length((void **)arg) > 1)
		ft_putstr_fd("Don't shoot anything!\n", STDERR_FILENO);
	else
	{
		sh->prompt_color1 = PRPT_COL_MAG;
		sh->prompt_color2 = PRPT_COL_MAG;
		update_prompt(sh);
		ft_putstr_fd(PROMPT_COLOR_OPEN, STDOUT_FILENO);
		ft_putstr_fd("  bigerrno$ ", STDOUT_FILENO);
		ft_putstr_fd(PROMPT_COLOR_CLOSE, STDOUT_FILENO);
		get_terminal_size(rows_cols);
		animate_shoot(rows_cols[1]);
		*color = E_PINK;
		ft_putstr_fd("\a", STDOUT_FILENO);
		ft_putstr_fd("\033[H\033[J", STDOUT_FILENO);
	}
	return (0);
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
	if (pipe(pipefd) < 0)
		return (ft_putstr_fd("Impossible pipe creation\n", STDERR_FILENO));
	cpid = fork();
	if (cpid < 0)
		return (ft_putstr_fd("Impossible child creation\n", STDERR_FILENO));
	if (cpid == 0)
		execute_in_child(pipefd);
	else
	{
		execute_in_parent(pipefd, rows_cols);
		waitpid(cpid, NULL, 0);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

static void	execute_in_child(int pipefd[2])
{
	char	buffer[124];
	int		n_bytes;

	close(pipefd[0]);
	ft_putstr_fd("\e[18t", STDOUT_FILENO);
	n_bytes = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
	if (n_bytes > 0)
	{
		buffer[n_bytes] = '\0';
		ft_putstr_fd(buffer, pipefd[1]);
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
		ft_putstr_fd("Erreur lors de la récupération des dimensions du "
			"terminal.\n", STDERR_FILENO);
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
		ft_putstr_fd("\r", STDOUT_FILENO);
		i = -1;
		while (++i < pixel_pos)
			ft_putstr_fd(" ", STDOUT_FILENO);
		ft_putstr_fd("\e[35m•\e[0m", STDOUT_FILENO);
		i = 0;
		while (i < 80000000 / v)
			++i;
		v += 0.2;
		if (v > 10.0)
			v = 10.0;
	}
	ft_putstr_fd("\r", STDOUT_FILENO);
	i = -1;
	while (++i < cols)
		ft_putstr_fd(" ", STDOUT_FILENO);
	ft_putstr_fd("\r", STDOUT_FILENO);
}

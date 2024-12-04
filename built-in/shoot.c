/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:49:32 by lchauffo          #+#    #+#             */
/*   Updated: 2024/12/04 15:48:11 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	trim_newline(char *str);
void	execute_in_child(int pipefd[2]);
void	execute_in_parent(int pipefd[2], int *rows_cols);

static void	draw_bullet(char **dot, int *pixel_pos, float *v)
{
	int		i;
	int		j;

	write(STDOUT_FILENO, "\r", 1);
	i = -1;
	while (++i < *pixel_pos)
		write(STDOUT_FILENO, " ", 1);
	write(STDOUT_FILENO, *dot, ft_strlen(*dot));
	j = 0;
	while (j < 80000000 / *v)
		j++;
	(*pixel_pos)++;
	*v += 0.2;
	if (*v > 10.0)
		*v = 10.0;
}

static void	animate_shoot(int cols)
{
	int		pixel_pos;
	int		i;
	float	v;
	char	*dot;

	pixel_pos = 0;
	v = 0.1;
	dot = ft_strdup("\e[35m•\e[0m");
	while (pixel_pos < cols && !g_signum)
		draw_bullet(&dot, &pixel_pos, &v);
	write(STDOUT_FILENO, "\r", 1);
	i = -1;
	while (++i < cols)
		write(STDOUT_FILENO, " ", 1);
	write(STDOUT_FILENO, "\r", 1);
	free(dot);
}

void	get_terminal_size(int *rows_cols)
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

int	bigerrno_shoot(t_sh *sh, enum e_color *color, char **arg)
{
	int		rows_cols[2];

	if (bn_linelen(arg) > 1)
		perror("Don't shoot anything");
	if (sh->prompt_color1)
		free(sh->prompt_color1);
	sh->prompt_color1 = ft_strdup(PRPT_COL_MAG);
	if (sh->prompt_color2)
		free(sh->prompt_color2);
	sh->prompt_color2 = ft_strdup(PRPT_COL_MAG);
	update_prompt(sh);
	write(1, PROMPT_COLOR_OPEN, ft_strlen(PROMPT_COLOR_OPEN));
	write(1, "  minishell$ ", 14);
	write(1, PROMPT_COLOR_CLOSE, ft_strlen(PROMPT_COLOR_CLOSE));
	get_terminal_size(rows_cols);
	animate_shoot(rows_cols[1]);
	*color = E_PINK;
	ft_putstr_fd("\a", 1);
	ft_putstr_fd("\033[H\033[J", 1);
	return (TRUE);
}

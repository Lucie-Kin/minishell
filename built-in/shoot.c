/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:49:32 by lchauffo          #+#    #+#             */
/*   Updated: 2024/11/04 15:11:01 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	animate_shoot(int rows, int cols)
{
	int		pixel_pos;
	int		i;
	int		j;
	float	v;
	char	*dot;

	pixel_pos = 0;
	v = 0.1;
	(void)rows;
	dot = strdup("\e[35m•\e[0m");
	while (pixel_pos < cols)
	{
		write(STDOUT_FILENO, "\r", 1);
		i = -1;
		while (++i < pixel_pos)
			write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, dot, strlen(dot));
		j = 0;
		while (j < 80000000 / v)
			j++;
		pixel_pos++;
		v += 0.2;
		if (v > 10.0)
			v = 10.0;
	}
	write(STDOUT_FILENO, "\r", 1);
	i = -1;
	while (++i < cols)
		write(STDOUT_FILENO, " ", 1);
	write(STDOUT_FILENO, "\r", 1);
	free(dot);
}

void	trim_newline(char *str)
{
	size_t	len;

	len = strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}

void	execute_in_child(int pipefd[2])
{
	char	buffer[124];

	close(pipefd[0]);
	write(STDOUT_FILENO, "\e[18t", 6);
	if (read(STDIN_FILENO, buffer, sizeof(buffer) - 1) > 0)
	{
		buffer[sizeof(buffer) - 1] = '\0';
		write(pipefd[1], buffer, strlen(buffer));
	}
	close(pipefd[1]);
	exit(0);
}

void	execute_in_parent(int pipefd[2], int *rows_cols)
{
	char	**split;
	char	buffer[124];

	close(pipefd[1]);
	read(pipefd[0], buffer, sizeof(buffer) - 1);
	buffer[sizeof(buffer) - 1] = '\0';
	split = ft_split(buffer + 4, ';');
	if (split && split[0] && split[1])
	{
		rows_cols[0] = atoi(split[0]);
		rows_cols[1] = atoi(split[1]);
	}
	else
		printf("Erreur lors de la récupération des dimensions du terminal.\n");
	bn_freetab(split);
	close(pipefd[0]);
}

void	get_terminal_size(int *rows_cols)
{
	int				cpid;
	int				pipefd[2];
	struct termios	oldt;
	struct termios	newt;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
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

int	bigerrno_shoot(char	**arg)
{
	// char	*command;
	// int		prompt_in_rose;
	int		rows_cols[2];

	if (bn_linelen(arg) > 1)
		perror("Don't shoot anything");
	get_terminal_size(rows_cols);
	return (TRUE);
}

// int	main(void)
// {
// 	char	*command;
// 	int		prompt_in_rose;
// 	int		rows_cols[2];

// 	prompt_in_rose = 0;
// 	get_terminal_size(rows_cols);
// 	while (1)
// 	{
// 		if (prompt_in_rose)
// 		{
// 			write(1, PROMPT_COLOR_OPEN, strlen(PROMPT_COLOR_OPEN));
// 			write(1, "minishell$ ", 12);
// 			write(1, PROMPT_COLOR_CLOSE, strlen(PROMPT_COLOR_CLOSE));
// 		}
// 		else
// 			write(1, "minishell$ ", 12);
// 		command = get_next_line(STDIN_FILENO);
// 		if (!command)
// 		{
// 			write(1, "Fin de fichier ou erreur de lecture.\n", 38);
// 			break ;
// 		}
// 		trim_newline(command);
// 		if (strcmp(command, "shoot") == 0)
// 		{
// 			prompt_in_rose = 1;
// 			animate_shoot(rows_cols[0], rows_cols[1]);
// 		}
// 		else if (strcmp(command, "exit") == 0)
// 		{
// 			prompt_in_rose = 0;
// 			free(command);
// 			break ;
// 		}
// 		else
// 		{
// 			write(STDOUT_FILENO, "Commande inconnue : ", 20);
// 			write(STDOUT_FILENO, command, strlen(command));
// 			write(STDOUT_FILENO, "\n", 1);
// 		}
// 		free(command);
// 	}
// 	return (0);
// }

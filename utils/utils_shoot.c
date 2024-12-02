/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_shoot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:51:50 by lchauffo          #+#    #+#             */
/*   Updated: 2024/12/02 17:03:05 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	trim_newline(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}

void	execute_in_child(int pipefd[2])
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

void	execute_in_parent(int pipefd[2], int *rows_cols)
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
	bn_freetab(split);
	close(pipefd[0]);
}

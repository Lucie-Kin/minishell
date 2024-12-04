/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:31:07 by lchauffo          #+#    #+#             */
/*   Updated: 2024/12/04 15:36:18 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define MATRIX "clear; echo -e \"\\e[48;5;16m\"; while :; \
do echo $LINES $COLUMNS $(( $RANDOM % $COLUMNS)) \
$(( $RANDOM % 73 )); sleep 0.05; done \
| awk '{ letters=\"abcdefghijklmnopqrstuvwxyz\
ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789@#$%^&*() \"; \
c=$4; letter=substr(letters,c,1); a[$3]=0; for (x in a) { o=a[x]; a[x]=a[x]+1; \
printf \"\\033[%s;%sH\\033[1;32m%s\", o, x, letter; \
printf \"\\033[%s;%sH\\033[1;37m%s\\033[0;0H\", a[x], x, letter; \
if (a[x] >= $1) { a[x]=0; } }}'"

int	bigerrno_matrix(t_sh *sh, char **arg)
{
	pid_t	pid;
	int		status;
	char	*args[4];

	if (bn_linelen(arg) > 1)
		return (perror("Don't matrix anything"), 42);
	write(STDOUT_FILENO, "\x0c", 1);
	ft_putstr_fd("\033[H\033[J", 1);
	pid = fork();
	if (pid == -1)
		return (perror("fork failed"), 1);
	if (pid == 0)
	{
		args[0] = "/bin/bash";
		args[1] = "-c";
		args[2] = MATRIX;
		args[3] = NULL;
		execve("/bin/bash", args, convert_to_tab(sh->env));
		perror("execve failed");
		exit(1);
	}
	waitpid(pid, &status, 0);
	write(STDOUT_FILENO, "\x0c", 1);
	return (WIFEXITED(status) || 1);
}

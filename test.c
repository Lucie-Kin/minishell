/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:54:35 by lchauffo          #+#    #+#             */
/*   Updated: 2024/12/03 20:05:37 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MATRIX "clear; echo -e \"\\e[1;40m\"; while :; do echo $LINES $COLUMNS $(( $RANDOM % $COLUMNS)) $(( $RANDOM % 72 )); sleep 0.05; done | awk '{ letters=\"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789@#$%^&*()\"; c=$4; letter=substr(letters,c,1); a[$3]=0; for (x in a) { o=a[x]; a[x]=a[x]+1; printf \"\\033[%s;%sH\\033[2;32m%s\", o, x, letter; printf \"\\033[%s;%sH\\033[1;37m%s\\033[0;0H\", a[x], x, letter; if (a[x] >= $1) { a[x]=0; } }}'"

int main() {
	char *input = readline("> Minishell: ");
	if (input == NULL) {
		perror("Failed to read input");
		return 1;
	}
	if (strcmp(input, "matrix") == 0) {
		printf("\x0c");  // Clear the screen at the beginning
		pid_t pid = fork();
		if (pid == -1) {
			perror("fork failed");
			free(input);
			return 1;
		} else if (pid == 0) {
			char *args[] = {"/bin/bash", "-c", MATRIX, NULL};
			execve("/bin/bash", args, NULL);
			perror("execve failed");
			exit(1);
		} else {
			int status;
			waitpid(pid, &status, 0);
			printf("\x0c");  // Clear the screen when returning to the parent
			if (WIFEXITED(status)) {
				printf("Matrix exited with status %d\n", WEXITSTATUS(status));
			} else {
				printf("Matrix terminated abnormally\n");
			}
		}
	} else {
		printf("Invalid input\n");
	}
	free(input);
	return 0;
}

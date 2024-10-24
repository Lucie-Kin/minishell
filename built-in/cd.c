/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:13:59 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/24 15:56:42 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_username(t_env **env2)
{
	int		pipefd[2];
	int		cpid;
	char	*username;

	if (pipe(pipefd) == -1)
		return (perror("Impossible pipe creation\n"), NULL);
	cpid = fork();
	if (cpid == -1)
		return (perror("Impossible fork creation\n"), NULL);
	if (cpid == 0)
		exec_in_child(env2, "/bin/whoami", pipefd);
	wait(NULL);
	username = get_next_line(pipefd[0]);
	close(pipefd[1]);
	close(pipefd[0]);
	return (username);
}

char	*get_absolute_path(t_env **env2)
{
	int		pipefd[2];
	int		cpid;
	char	*abs_path;
	char	*abs_cmd;

	abs_cmd = ft_strjoin("/bin/getent passwd ", get_username(env2));
	if (pipe(pipefd) == -1)
		return (perror("Impossible pipe creation\n"), NULL);
	cpid = fork();
	if (cpid == -1)
		return (perror("Impossible fork creation\n"), NULL);
	if (cpid == 0)
		exec_in_child(env2, abs_cmd, pipefd);
	wait(NULL);
	abs_path = find_absolute_path(pipefd);
	close(pipefd[1]);
	close(pipefd[0]);
	return (abs_path);
}

t_env	*find_key(t_env **env2, char *key, int print_err)
{
	t_env	*list;

	list = *env2;
	if (!key || !list)
	{
		if (print_err)
			perror("No env or key found\n");
		return (NULL);
	}
	while (list)
	{
		if (bn_isstrstr(list->key, key) == TRUE)
			return (list);
		list = list->next;
	}
	if (print_err)
		perror("Key not found\n");
	return (NULL);
}

void	change_directory(char *path)
{
	if (chdir(path) != 0)
		perror("2 Failed to change directory");
}

void	bigerrno_cd(t_env **env, t_env **local, char **arg)
{
	int	arg_len;

	arg_len = bn_linelen(arg);
	if (!env)
		return (perror("env is NULL\n"));
	if ((arg_len) > 2)
		perror("Too many arguments");
	else if (!arg[1] && find_key(local, "HOME", FALSE))//
		change_directory(find_key(local, "HOME", FALSE)->value);
	else if (!arg[1])
		change_directory(find_key(env, "HOME", TRUE)->value);
	else if (arg[1][0] == '~' && arg[1][0] == '\0')
		change_directory(get_absolute_path(env));
	else if (ft_strcmp(arg[1], "-") == 0)
	{
		if (!(chdir(find_key(env, "OLDPWD", TRUE)->value) == 0 || chdir(add_node
					(env, "OLDPWD", getcwd(NULL, 0))->value) == 0))
			perror("3 Failed to change directory");
	}
	else
		change_directory(arg[1]);
	update_pwd(env);
}

// sh->ex->pl.cmdl[sh->ex->pl.index]
// sh->ex->pl.cmdl[sh->ex->pl.index][index] == cd
// nombre de cmd = sh->ex->pl.len
// char **cmdl
// ["cd", "truc", "machin", NULL]

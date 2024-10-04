/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:13:59 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/02 17:11:22 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_absolute_path(t_list **env2)
{
	int		pipefd[2];
	int		cpid;
	char	*abs_path;

	if (pipe(pipefd) == -1)
		return (perror("Impossible pipe creation\n"), NULL);
	cpid = fork();
	if (cpid == -1)
		return (perror("Impossible fork creation\n"), NULL);
	if (cpid == 0)
		exec_in_child(env2, "getent passwd $(whoami)", pipefd);
	wait(NULL);
	abs_path = find_absolute_path(pipefd);
	close(pipefd[1]);
	close(pipefd[0]);
	return (abs_path);
}

t_list	*find_key(t_list **env2, char *key)
{
	t_list	*list;

	list = *env2;
	if (!key || !list)
		return (perror("No env or key found\n"), NULL);
	while (list)
	{
		if (isstrstr(list->key, key) == TRUE)
			return (list);
		list = list->next;
	}
	perror("Key not found\n");
	return (NULL);
}

void	change_directory(char *path)
{
	if (chdir(path) != 0)
		perror("2 Failed to change directory");
}

void	bigerrno_cd(int argc, char **arg, t_list **env2, int cd)
{
	if (!env2)
		return (perror("env is NULL\n"));
	if ((argc - cd) > 2)
		perror("Too many arguments");
	else if (!arg[cd + 1])
		change_directory(find_key(env2, "HOME")->value);
	else if (arg[cd + 1][0] == '~' && arg[cd + 1][0] == '\0')
		change_directory(get_absolute_path(env2));
	else if (ft_strcmp(arg[cd + 1], "-") == 0)
	{
		if (!(chdir(find_key(env2, "OLDPWD")->value) == 0 || chdir(add_node
					(env2, "OLDPWD", getcwd(NULL, 0))->value) == 0))
			perror("3 Failed to change directory");
	}
	else
		change_directory(arg[cd + 1]);
	update_pwd(env2);
}

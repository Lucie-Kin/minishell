/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:35:04 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/14 13:38:17 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**convert_charchar(t_list **env2)
{
	char	**copy;
	int		i;

	i = 0;
	copy = malloc(sizeof(char *) * list_size(env2));
	if (!copy)
		return (perror("Failure to convert t_list ** to char **"), NULL);
	while (copy[i])
	{
		copy[i] = ft_strdup((*env2)->key);
		copy[i] = ft_strjoin(copy[i], "=");
		copy[i] = ft_strjoin(copy[i], (*env2)->value);
		i++;
	}
	return (copy);
}

void	exec_in_child(t_list **env2, char *cmd, int pipefd[2])
{
	char	**args;
	char	**path;
	char	*join;
	int		i;

	i = 0;
	dup2(pipefd[0], STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	args = ft_split(cmd, ' ');
	path = ft_split(find_key(env2, "PATH")->value, ':');
	while (path[i])
	{
		join = ft_strjoin(path[i], cmd);
		if (access(join, X_OK) == 0)
			execve(join, args, convert_charchar(env2));
		free(join);
		i++;
	}
}

// login:x:101942:4224:Name Surname:/home/login:/bin/zsh
char	*find_absolute_path(int pipefd[2])
{
	char	*line;
	char	**abs_path;
	char	*home;

	line = get_next_line(pipefd[0]);
	abs_path = ft_split(line, ':');
	free(line);
	home = ft_strdup(abs_path[5]);
	bn_freetab(abs_path);
	return (home);
}

t_list	*add_node(t_list **env2, char *key, char *value)
{
	t_list	*new;
	t_list	*lst;

	lst = *env2;
	new = lst_new(ft_strdup(key), ft_strdup(value));
	if (!new)
		return (lst_clear(&lst), NULL);
	lstadd_back(&lst, new);
	return (new);
}

void	update_pwd(t_list **env2)
{
	t_list	*pwd;
	t_list	*oldpwd;

	pwd = *env2;
	oldpwd = *env2;
	pwd = find_key(env2, "PWD");
	if (!pwd)
		return (perror("Key not found\n"));
	oldpwd = find_key(env2, "OLDPWD");
	if (!oldpwd)
		return (perror("Key not found\n"));
	free(oldpwd->value);
	oldpwd->value = ft_strdup(pwd->value);
	free(pwd->value);
	pwd->value = getcwd(NULL, 0);
}
	// printf("\nOldpwd pointing to: %p, %s=%s\n",
	// 	oldpwd, oldpwd->key, oldpwd->value);
	// printf("\nPwd pointing to: %p, %s=%s\n", pwd, pwd->key, pwd->value);

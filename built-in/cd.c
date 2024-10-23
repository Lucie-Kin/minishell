/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:13:59 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/23 16:39:45 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

t_list	*find_key(t_list **env2, char *key)
{
	t_list	*list;

	list = *env2;
	if (!key || !list)
		return (perror("No env or key found\n"), NULL);
	while (list)
	{
		if (bn_isstrstr(list->key, key) == TRUE)
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

void	bigerrno_cd(t_list **env2, char **arg)
{
	int	arg_len;

	arg_len = bn_linelen(arg);
	if (!env2)
		return (perror("env is NULL\n"));
	if ((arg_len) > 2)
		perror("Too many arguments");
	else if (!arg[1])
		change_directory(find_key(env2, "HOME")->value);
	else if (ft_strcmp(arg[1], "-") == 0)
	{
		if (!(chdir(find_key(env2, "OLDPWD")->value) == 0 || chdir(add_node
					(env2, "OLDPWD", getcwd(NULL, 0))->value) == 0))
			perror("3 Failed to change directory");
	}
	else
		change_directory(arg[1]);
	update_pwd(env2);
}

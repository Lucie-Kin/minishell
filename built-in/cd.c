/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:13:59 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/24 19:49:33 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*add_node(t_env **env, char *key, char *value)
{
	t_env	*new;
	t_env	*lst;

	lst = *env;
	new = lst_new(ft_strdup(key), ft_strdup(value));
	if (!new)
		return (lst_clear(&lst), NULL);
	lstadd_back(&lst, new);
	return (new);
}

void	update_pwd(t_env **env)
{
	t_env	*pwd;
	t_env	*oldpwd;

	pwd = *env;
	oldpwd = *env;
	pwd = find_key(env, "PWD", TRUE);
	if (!pwd)
		return ;//return (perror("Key not found\n"));
	oldpwd = find_key(env, "OLDPWD", TRUE);
	if (!oldpwd)
		return ;//return (perror("Key not found\n"));
	free(oldpwd->value);
	oldpwd->value = ft_strdup(pwd->value);
	free(pwd->value);
	pwd->value = getcwd(NULL, 0);
}

t_env	*find_key(t_env **env, char *key, int print_err)
{
	t_env	*list;

	list = *env;
	if (!key || !list)
	{
		//if (print_err)
		//	perror("No env or key found\n");
		return (NULL);
	}
	while (list)
	{
		if (bn_isstrstr(list->key, key) == TRUE)
			return (list);
		list = list->next;
	}
	//if (print_err)
	//	perror("Key not found\n");
	return (NULL);
}

void	change_directory(char *path)
{
	if (chdir(path) != 0)
	{
		//perror("2 Failed to change directory");
	}
}

void	bigerrno_cd(t_env **env, t_env **local, char **arg)
{
	int	arg_len;

	arg_len = bn_linelen(arg);
	if (!env)
		return ;//return (perror("env is NULL\n"));
	if ((arg_len) > 2)
	{
		//perror("Too many arguments");
	}
	else if (!arg[1] && find_key(local, "HOME", FALSE))
		change_directory(find_key(local, "HOME", FALSE)->value);
	else if (!arg[1])
		change_directory(find_key(env, "HOME", TRUE)->value);
	else if (ft_strcmp(arg[1], "-") == 0)
	{
		if (!(chdir(find_key(env, "OLDPWD", TRUE)->value) == 0 || chdir(add_node
					(env, "OLDPWD", getcwd(NULL, 0))->value) == 0))
		{
			//perror("3 Failed to change directory");
		}
	}
	else
		change_directory(arg[1]);
	update_pwd(env);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:13:59 by lchauffo          #+#    #+#             */
/*   Updated: 2024/11/07 18:42:38 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*add_node(t_env **lst, char *key, char *value)
{
	t_env	*new;

	new = lst_new(key, value);
	if (!new || !new->key)
	{
		fprintf(stderr, "Error creating new node or duplicating key/value\n");
		if (new)
			free(new);
		return (lst_clear(lst), NULL);
	}
	lstadd_back(lst, new);
	return (new);
}

void	update_pwd(t_env **env)
{
	t_env	*pwd;
	t_env	*oldpwd;

	pwd = *env;
	oldpwd = *env;
	pwd = find_key(*env, "PWD");
	if (!pwd)
		return (perror("Key not found1\n"));
	oldpwd = find_key(*env, "OLDPWD");
	if (!oldpwd)
		return (perror("Key not found2\n"));
	free(oldpwd->value);
	oldpwd->value = ft_strdup(pwd->value);
	free(pwd->value);
	pwd->value = getcwd(NULL, 0);
}

t_env	*find_key(t_env *env, char *key)
{
	t_env	*list;

	list = env;
	if (!key || !list)
		return (NULL);
	while (list)
	{
		if (bn_isstrstr(list->key, key) == TRUE)
			return (list);
		list = list->next;
	}
	return (NULL);
}

int	change_directory(char *path)
{
	if (ft_strcmp(path, "HOME") == 0)
	{
		output_error(EPERM,
			compose_err_msg(SHELL, "cd", NULL, "HOME not set"));
		return (EPERM);
	}
	if (chdir(path) != 0)
	{
		if (access(path, F_OK) == 0)
			output_error(EPERM,
				compose_err_msg(SHELL, "cd", path, strerror(EACCES)));
		else
			output_error(EPERM,
				compose_err_msg(SHELL, "cd", path, strerror(ENOENT)));
		return (EPERM);
	}
	return (0);
}

/*
	- If $PWD is unset, and `cd` is used, update it in the hidden list only.
	It remains in the hidden list until `export` is used (I think).
	- If $PWD exists at all, even if hidden, `get_env` should return its 
	value.
*/
int	bigerrno_cd(t_env **env, t_env **hidden, t_env **local, char **arg)
{
	int	cod_err;

	cod_err = 0;
	if (!env)
		return (0);
	update_env(env, hidden);
	if (bn_linelen(arg) > 2)
		perror("Too many arguments");
	else if (!arg[1] && find_key(*local, "HOME"))
		cod_err = change_directory(find_key(*local, "HOME")->value);
	else if (!arg[1] && find_key(*env, "HOME"))
		cod_err = change_directory(find_key(*env, "HOME")->value);
	else if (!arg[1])
		change_directory("HOME");
	else if (ft_strcmp(arg[1], "-") == 0)
	{
		printf("%s\n", find_key(*env, "OLDPWD")->value);
		if (!(chdir(find_key(*env, "OLDPWD")->value) == 0 || chdir
				(add_node(env, "OLDPWD", getcwd(NULL, 0))->value) == 0))
			perror("lol");
	}
	else
		cod_err = change_directory(arg[1]);
	update_pwd(env);
	return (cod_err);
}

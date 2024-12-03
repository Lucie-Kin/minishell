/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:28:32 by lchauffo          #+#    #+#             */
/*   Updated: 2024/12/03 15:19:45 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	bn_strnlen(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (c == '\n')
		return (-1);
	return (i);
}

// void	list_in_p_order(t_env **env)
// {
// 	t_env	*tmp_dup;
// 	t_env	*smallest;
// 	t_env	*next_small;
// 	t_env	*biggest;

// 	if (!env || !*env)
// 		return ;
// 	tmp_dup = list_dup(*env);
// 	if (!tmp_dup)
// 		return ;
// 	smallest = find_smallest_p(env);
// 	biggest = find_biggest_p(env);
// 	if (!smallest || !biggest)
// 		return (lst_clear(&tmp_dup));
// 	swap_node_content(tmp_dup, smallest);
// 	while (smallest != biggest)
// 	{
// 		next_small = next_smallest(env, smallest);
// 		if (!next_small)
// 			break ;
// 		swap_node_content(tmp_dup, next_small);
// 		tmp_dup = tmp_dup->next;
// 		smallest = next_small;
// 	}
// 	lst_clear(&tmp_dup);
// }

void	list_in_p_order(t_env **env)
{
	t_env	*smallest;
	t_env	*next_small;
	t_env	*biggest;

	if (!env || !*env)
		return ;
	smallest = find_smallest_p(env);
	biggest = find_biggest_p(env);
	if (!smallest || !biggest)
		return ;
	while (smallest != biggest)
	{
		next_small = next_smallest(env, smallest);
		if (!next_small)
			break ;
		swap_node_content(smallest, next_small);
		smallest = next_small;
	}
}

void	get_small_env(t_env	**lst)
{
	t_env	*new;

	new = lst_new("PWD", getcwd(NULL, 0));
	if (!new)
		lst_clear(lst);
	lstadd_back(lst, new);
	new = lst_new("PROMPT_COMMAND", "RETRN_VAL=$?;logger -p local6.debug"
			" \"$(history 1 | sed \"s/^[ ]*[0-9]\\+[ ]*//\" ) [$RETRN_VAL]\"");
	if (!new)
		lst_clear(lst);
	lstadd_back(lst, new);
	new = lst_new("SHLVL", "1");
	if (!new)
		lst_clear(lst);
	lstadd_back(lst, new);
	new = lst_new("_", "./minishell");
	if (!new)
		lst_clear(lst);
	lstadd_back(lst, new);
	new = lst_new("TERM", "xterm-256color");
	if (!new)
		lst_clear(lst);
	lstadd_back(lst, new);
}

void	copy_to_list(char **env, t_env **lst)
{
	t_env	*new;
	char	*key;
	char	*value;
	int		size;
	int		i;

	i = 0;
	while (env[i])
	{
		size = bn_strnlen(env[i], '=');
		key = ft_substr(env[i], 0, size);
		if (!key)
			break ;
		value = ft_strdup(getenv(key));
		new = lst_new(key, value);
		free(key);
		free(value);
		if (!new)
			return (lst_clear(lst));
		lstadd_back(lst, new);
		i++;
	}
}

// void	debug_copy_env(char **env, t_env **lst, int size)
// {
// 	int		i;

// 	i = 0;
// 	while (env[i] && i < size)
// 	{
// 		if ()
// 	}
// }

t_env	*convert_to_list(char **env)
{
	t_env	*lst;

	lst = NULL;
	if (!env[0])
		get_small_env(&lst);
	else
		copy_to_list(env, &lst);
	if (lst)
		list_in_p_order(&lst);
	return (lst);
}

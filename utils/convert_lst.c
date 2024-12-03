/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:28:32 by lchauffo          #+#    #+#             */
/*   Updated: 2024/12/03 19:29:00 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	get_small_env(t_env	**lst);
static void	copy_to_lst(char **env, t_env **lst);
static void	lst_in_p_order(t_env **env);

t_env	*convert_to_lst(char **env)
{
	t_env	*lst;

	lst = NULL;
	if (!env[0])
		get_small_env(&lst);
	else
		copy_to_lst(env, &lst);
	if (lst)
		lst_in_p_order(&lst);
	return (lst);
}

void	swap_node_content(t_env *s1, t_env *s2)
{
	int		tmp_bool;
	char	*tmp_key;
	char	*tmp_value;

	tmp_bool = s1->withvalue;
	s1->withvalue = s2->withvalue;
	s2->withvalue = tmp_bool;
	tmp_key = s1->key;
	s1->key = s2->key;
	s2->key = tmp_key;
	tmp_value = s1->value;
	s1->value = s2->value;
	s2->value = tmp_value;
}

static void	get_small_env(t_env	**lst)
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

static void	copy_to_lst(char **env, t_env **lst)
{
	t_env	*new;
	char	*key;
	char	*value;
	int		size;
	int		i;

	i = 0;
	while (env[i])
	{
		size = continued_occurence(env[i], '=');
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

static void	lst_in_p_order(t_env **env)
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

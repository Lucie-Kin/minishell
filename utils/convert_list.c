/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:28:32 by lchauffo          #+#    #+#             */
/*   Updated: 2024/11/04 16:18:46 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	list_in_p_order(t_env **env)
{
	t_env	*tmp_dup;
	t_env	*smallest;
	t_env	*next_small;
	t_env	*biggest;

	tmp_dup = list_dup(*env);
	smallest = find_smallest_p(env);
	swap_node_content(&tmp_dup, &smallest);
	biggest = find_biggest_p(env);
	if (!smallest || !biggest || !env)
		return (perror("Nothing to be printed"));
	while (smallest != biggest)
	{
		next_small = next_smallest(env, smallest);
		swap_node_content(&tmp_dup, &next_small);
		tmp_dup = tmp_dup->next;
		smallest = next_small;
	}
	lst_clear(&tmp_dup);
}

// PROMPT_COMMAND=
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
}

t_env	*convert_to_list(char **env)
{
	t_env	*lst;
	t_env	*new;
	char	*key;
	int		size;
	int		i;

	i = 0;
	lst = NULL;
	if (!env[0])
		get_small_env(&lst);
	else
	{
		while (env[i])
		{
			size = bn_strnlen(env[i], '=');
			key = bn_strldup(env[i], size);
			new = lst_new(key, ft_strdup(getenv(key)));
			if (!new)
				lst_clear(&lst);
			lstadd_back(&lst, new);
			i++;
		}
	}
	return (lst);
}

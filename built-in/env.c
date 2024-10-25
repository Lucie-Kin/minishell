/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:14:16 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/25 19:43:32 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_print(t_env *to_print)
{
	if (DBUG)
		printf("p=%p\t%s=%s\n", to_print, to_print->key, to_print->value);
	else
		printf("%s=%s\n", to_print->key, to_print->value);
}

void	print_in_p_order(t_env **to_print, t_env **not_to_print)
{
	t_env	*p_order;
	t_env	*smallest;
	t_env	*next_small;
	t_env	*biggest;

	p_order = *to_print;
	smallest = find_smallest_p(&p_order);
	biggest = find_biggest_p(&p_order);
	if (!smallest || !biggest || !p_order)
		return (perror("Nothing to be printed"));
	if (smallest->withvalue == TRUE && !find_key(*not_to_print,
			smallest->key, FALSE))
		env_print(smallest);
	while (smallest != biggest)
	{
		next_small = next_smallest(&p_order, smallest);
		if (next_small && next_small->withvalue == TRUE
			&& !find_key(*not_to_print, next_small->key, FALSE))
			env_print(next_small);
		smallest = next_small;
	}
	lst_clear(not_to_print);
}

void	error_management(char *cmd, char *wrong_arg, char *msg_error)
{
	printf("%s: \'%s\': %s", cmd, wrong_arg, msg_error);
}

void	bigerrno_env(t_env **env, t_env **local, char **arg)
{
	(void)local;
	if (!arg[1])
	{
		// print_in_p_order(local, NULL);
		print_in_p_order(env, local);
	}
	else if (arg[1])
	{
		if (access(arg[1], F_OK) == TRUE)
			return (error_management(arg[0], arg[1],
					"Permission denied"));
		else
			return (error_management(arg[0], arg[1],
					"No such file or directory"));
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:14:16 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/21 18:56:36 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_in_p_order(t_list **env2)
{
	t_list	*smallest;
	t_list	*next_small;
	t_list	*biggest;
	t_list	*p_order;

	p_order = *env2;
	smallest = find_smallest_p(&p_order);
	biggest = find_biggest_p(&p_order);
	if (!smallest || !biggest || !p_order)
		return (perror("No env found"));
	if (smallest->withvalue == TRUE)
		printf("p=%p\t%s=%s\n", smallest, smallest->key, smallest->value);
	while (smallest != biggest)
	{
		next_small = next_smallest(&p_order, smallest);
		if (next_small && next_small->withvalue == TRUE)
			printf("p=%p\t%s=%s\n", next_small, next_small->key,
				next_small->value);
		smallest = next_small;
	}
}

void	error_management(char *cmd, char *wrong_arg, char *msg_error)
{
	printf("%s: \'%s\': %s", cmd, wrong_arg, msg_error);
}

void	bigerrno_env(t_list **env2, char **arg)
{
	if (!arg[1])
		print_in_p_order(env2);
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

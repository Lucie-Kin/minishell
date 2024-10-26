/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:41:14 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/22 13:42:12 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*find_smallest_p(t_env **p_order)
{
	t_env	*tmp;
	t_env	*smallest;

	tmp = *p_order;
	smallest = *p_order;
	while (tmp)
	{
		if (smallest > tmp)
			smallest = tmp;
		tmp = tmp->next;
	}
	return (smallest);
}

t_env	*find_biggest_p(t_env **p_order)
{
	t_env	*tmp;
	t_env	*biggest;

	tmp = *p_order;
	biggest = *p_order;
	while (tmp)
	{
		if (biggest < tmp)
			biggest = tmp;
		tmp = tmp->next;
	}
	return (biggest);
}

t_env	*next_smallest(t_env **p_order, t_env *smallest)
{
	t_env	*next_small;
	t_env	*tmp;

	tmp = *p_order;
	next_small = NULL;
	if (!p_order)
		return (NULL);//return (perror("No struct list found"), NULL);
	if (!smallest)
		return (NULL);//return (perror("Node not found"), NULL);
	while (tmp)
	{
		if (tmp > smallest && (!next_small || tmp < next_small))
			next_small = tmp;
		tmp = tmp->next;
	}
	return (next_small);
}

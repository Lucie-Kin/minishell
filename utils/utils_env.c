/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:41:14 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/05 17:09:18 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*find_smallest_p(t_list **p_order)
{
	t_list	*tmp;
	t_list	*smallest;

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

t_list	*find_biggest_p(t_list **p_order)
{
	t_list	*tmp;
	t_list	*biggest;

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

t_list	*next_smallest(t_list **p_order, t_list *smallest)
{
	t_list	*next_small;
	t_list	*tmp;

	tmp = *p_order;
	next_small = NULL;
	if (!p_order)
		return (perror("No struct list found"), NULL);
	if (!smallest)
		return (perror("Node not found"), NULL);
	while (tmp)
	{
		if (tmp > smallest && (!next_small || tmp < next_small))
			next_small = tmp;
		tmp = tmp->next;
	}
	return (next_small);
}

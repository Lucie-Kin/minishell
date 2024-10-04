/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:41:14 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/02 17:33:46 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_list(t_list **list, char *prefix, int double_quote)
{
	t_list	*tmp;

	tmp = *list;
	if (!tmp)
		perror("Failure to read env");
	while (tmp)
	{
		if (prefix)
			printf("%s ", prefix);
		printf("%s=", tmp->key);
		if (double_quote == TRUE)
			printf("\" ");
		printf("%s\n", tmp->value);
		if (double_quote == TRUE)
			printf("\"");
		tmp = tmp->next;
	}
}

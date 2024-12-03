/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_parentheses.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:15:09 by libousse          #+#    #+#             */
/*   Updated: 2024/12/03 23:31:36 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*pl_skip_parentheses(char **tokens, size_t *i)
{
	size_t	parentheses;

	parentheses = 0;
	while (tokens[*i])
	{
		if (!ft_strcmp(tokens[*i], "("))
			++parentheses;
		else if (!ft_strcmp(tokens[*i], ")"))
			--parentheses;
		else if (!parentheses)
			break ;
		++*i;
	}
	return (tokens[*i]);
}

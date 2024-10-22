/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_len.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:10:40 by libousse          #+#    #+#             */
/*   Updated: 2024/10/22 15:48:11 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

size_t	get_pl_len(char **tokens)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 1;
	while (tokens[i])
	{
		if (!ft_strcmp(tokens[i], "|"))
			++len;
		++i;
	}
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bn_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:28:12 by lchauffo          #+#    #+#             */
/*   Updated: 2024/09/28 19:21:27 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbn.h"

int	bn_strnlen(char *s, char c)
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

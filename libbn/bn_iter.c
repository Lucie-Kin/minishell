/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bn_iter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:14:57 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/02 17:33:46 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbn.h"

int	bn_iter(char *s, char iter)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == iter)
		i++;
	if (s[i] != '\0')
		return (FALSE);
	return (TRUE);
}

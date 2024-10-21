/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bn_onlychar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:36:18 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/14 13:36:23 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbn.h"

int	bn_onlychar(char *s, char iter)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == iter)
		i++;
	if (s[i] != '\0')
		return (FALSE);
	return (TRUE);
}

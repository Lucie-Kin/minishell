/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bn_isstrstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:04:44 by lchauffo          #+#    #+#             */
/*   Updated: 2024/10/02 17:33:46 by lchauffo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbn.h"

int	bn_isstrstr(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1 || !str2)
		return (FALSE);
	while (str2[i] && str1[i] && str1[i] == str2[i])
		i++;
	if ((str1[i] == '\0' || str1[i] == '\n') && str2[i] == '\0')
		return (TRUE);
	return (FALSE);
}
